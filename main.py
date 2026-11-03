from datetime import date
import posixpath
import re

import yaml


def escape_latex_special_chars(text):
    """
    转义 LaTeX 特殊字符，包括: _ % $ # & { } ~ ^
    """
    special_chars = {
        '\\': r'\textbackslash{}',
        '&': r'\&',
        '%': r'\%',
        '$': r'\$',
        '#': r'\#',
        '_': r'\_',
        '{': r'\{',
        '}': r'\}',
        '~': r'\textasciitilde{}',
        '^': r'\textasciicircum{}'
    }
    # 使用正则表达式替换所有特殊字符
    return re.sub('|'.join(re.escape(key) for key in special_chars.keys()), 
                  lambda match: special_chars[match.group()], text)


def read_file(file_path):
    if not posixpath.isfile(file_path):
        raise FileNotFoundError(f"文件不存在：{file_path}")

    with open(file_path, "r", encoding="UTF-8") as f:
        return f.read()


def get_config(directory):
    config_paths = [
        posixpath.join(directory, "config.yml"),
        posixpath.join(directory, "config.yaml"),
    ]

    for config_path in config_paths:
        if not posixpath.isfile(config_path):
            continue

        with open(config_path, "r", encoding="UTF-8") as f:
            config = yaml.safe_load(f)
            if config is None:
                raise ValueError(f"配置文件 {config_path} 为空或有误")

            return config

    raise FileNotFoundError(f"目录 {directory} 未找到配置文件")


# 生成代码块 LaTeX 内容
def generate_latex_for_item(directory, item, depth, prefix=""):
    if "name" not in item:
        raise ValueError(f"目录 {directory} 配置文件有误（未配置 name）")

    name = escape_latex_special_chars(item.get('name'))

    if depth == 0:
        heading = f"\\section{{{name}}}\n"
    elif depth == 1:
        heading = f"\\subsection{{{name}}}\n"
    elif depth == 2:
        heading = f"\\subsubsection{{{name}}}\n"
    elif depth == 3:
        heading = f"\\paragraph{{{name}}}\n"
    else:
        raise ValueError(f"目录 {directory} 配置过深")

    if "code" in item and "code-pre" not in item:
        file_path = posixpath.join(directory, item["code"])
        if not posixpath.isfile(file_path):
            raise FileNotFoundError(f"code 文件不存在：{file_path}")
        caption = escape_latex_special_chars(item.get("caption", ""))
        source = read_file(file_path).splitlines()
        nonempty = [i + 1 for i, line in enumerate(source) if line.strip()]
        keep = nonempty[2] if len(nonempty) >= 3 else len(source)
        latex_parts = ["\\begin{minipage}{\\linewidth}\n", prefix, heading]
        if keep == len(source):
            latex_parts.append(f"\\lstinputlisting[caption={{{caption}}}]{{{file_path}}}\n")
        else:
            latex_parts.append(
                f"\\lstinputlisting[caption={{}},lastline={keep},belowskip=0pt]{{{file_path}}}\n"
            )
        latex_parts.append("\\end{minipage}\n")
        if keep < len(source):
            latex_parts.append(
                f"\\lstinputlisting[caption={{{caption}}},firstline={keep + 1},firstnumber={keep + 1},aboveskip=0pt]{{{file_path}}}\n"
            )
        if "code-post" in item:
            latex_parts.append(read_file(posixpath.join(directory, item["code-post"])))
            latex_parts.append("\n")
        return "\n".join(latex_parts)

    if "code-pre" in item:
        pre_path = posixpath.join(directory, item["code-pre"])
        contents = read_file(pre_path)
        first, separator, rest = contents.partition("\n\n")
        latex_parts = ["\\begin{minipage}{\\linewidth}\n", prefix, heading, first,
                       "\n\\end{minipage}\n"]
        if separator:
            latex_parts.extend([rest, "\n"])
        if "code" in item:
            file_path = posixpath.join(directory, item["code"])
            if not posixpath.isfile(file_path):
                raise FileNotFoundError(f"code 文件不存在：{file_path}")
            caption = escape_latex_special_chars(item.get("caption", ""))
            latex_parts.append(f"\\lstinputlisting[caption={{{caption}}}]{{{file_path}}}\n")
        if "code-post" in item:
            latex_parts.extend([read_file(posixpath.join(directory, item["code-post"])), "\n"])
        return "\n".join(latex_parts)

    latex_parts = [prefix, heading]
    for code_type in ["code-pre", "code", "code-post"]:
        if code_type not in item:
            continue

        file_path = posixpath.join(directory, item[code_type])

        if code_type == "code":
            if not posixpath.isfile(file_path):
                raise FileNotFoundError(f"{code_type} 文件不存在：{file_path}")

            caption = escape_latex_special_chars(item.get("caption", ""))
            latex_parts.append(
                f"\\lstinputlisting[caption={{{caption}}}]{{{file_path}}}\n"
            )
        else:
            contents = read_file(file_path)
            latex_parts.append(contents)
            latex_parts.append("\n")

    return "\n".join(latex_parts)


def entries(directory, depth=0):
    for item in get_config(directory).get("contents") or []:
        yield directory, item, depth
        if "directory" in item:
            yield from entries(posixpath.join(directory, item["directory"]), depth + 1)


def generate_latex_from_config(directory, columns=1):
    parts = []
    headings = []
    current = None
    current_env = None
    records = list(entries(directory))
    leaf_columns = [(i, item.get("columns", columns))
                    for i, (_, item, _) in enumerate(records) if "directory" not in item]
    final_columns = leaf_columns[-1][1]
    final_start = max((i for i, count in leaf_columns if count != final_columns), default=-1)
    for index, (directory, item, depth) in enumerate(records):
        if "directory" in item:
            headings.append(generate_latex_for_item(directory, item, depth))
            continue
        count = item.get("columns", columns)
        if count != current:
            if current is not None and current > 1:
                parts.append(f"\\end{{{current_env}}}\n\\par\n\\vspace{{3mm}}\n")
            elif current == 1:
                parts.append("\\end{widecontent}\n\\par\n\\vspace{3mm}\n")
            if count > 1:
                current_env = "multicols*" if index > final_start else "multicols"
                parts.append(f"\\begin{{{current_env}}}{{{count}}}\n")
            else:
                parts.append("\\begin{widecontent}\n")
                current_env = "widecontent"
            current = count
        prefix = "\n".join(headings)
        headings.clear()
        parts.append(generate_latex_for_item(directory, item, depth, prefix))
    if current is not None and current > 1:
        parts.append(f"\\end{{{current_env}}}\n")
    elif current == 1:
        parts.append("\\end{widecontent}\n")
    return "\n".join(parts)


def generate_latex(root_dir):
    config = get_config(root_dir)

    latex_pre = ""
    latex_post = ""

    if "latex-pre" in config:
        latex_pre_path = config["latex-pre"]
        latex_pre = read_file(latex_pre_path)

    def repl(m):
        key = m[1].lower()
        if key == "environment":
            return read_file(config[key]) if config.get(key) else ""
        text = config.get("text") or {}
        val = config.get(key) if key in ["title", "author"] else text.get(key)
        val = "" if val is None else str(val)
        if key == "date":
            val = date.today().strftime(val)
        return escape_latex_special_chars(val)

    latex_pre = re.sub(r"\{PLACEHOLDER:([A-Z-]+)\}", repl, latex_pre)

    if "latex-post" in config:
        latex_post_path = config["latex-post"]
        latex_post = read_file(latex_post_path)

    code_root = config.get("root-directory", "./templates")

    if not posixpath.isdir(code_root):
        raise NotADirectoryError(f"模板根目录不存在或不是一个目录：{code_root}")

    latex_content = generate_latex_from_config(code_root, config.get("columns", 1))

    return latex_pre + latex_content + latex_post


def write_latex_file(latex_content, output_file):
    try:
        with open(output_file, "w", encoding="UTF-8") as f:
            f.write(latex_content)
    except IOError as e:
        raise IOError(f"无法写入输出文件 {output_file}: {e}")


if __name__ == "__main__":
    root_dir = "./"

    latex_content = generate_latex(root_dir)
    output_file = "output.tex"
    write_latex_file(latex_content, output_file)
    write_latex_file("\\def\\TemplateMono{1}\n\\input{output.tex}\n", "output-bw.tex")
    print("LaTeX 文件已生成：output.tex、output-bw.tex")

