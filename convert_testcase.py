import ast
import re

def generate_cpp(ops, args, out):
    cpp = []
    print("\n\n--- C++ TESTCASE ---\n")
    cpp.append("vector<vector<string>> operations = {")
    for op, arg in zip(ops, args):
        if arg == "":
            cpp.append(f'    {{"{op}",""}},')
        else:
            cpp.append(f'    {{"{op}","{arg}"}},')
    cpp.append("};\n")

    cpp.append("vector<string> expected = {") 
    for val in out:
        cpp.append(f'    "{val}",')
    cpp.append("};")

    return "\n".join(cpp)

def normalize_list_block(block: str) -> str:
    """Fix spacing, convert null->None, remove stray chars."""
    block = block.replace("null", "None")     # FIX THE MAIN ISSUE
    block = re.sub(r'\[\s+\[', '[[', block)   # remove space between lists
    block = re.sub(r'\[\s+', '[', block)
    block = block.strip()
    return block

def clean_token(s):
    return ''.join(ch for ch in s if ch.isalnum())

def convert_testcase(input_file):
    with open(input_file, 'r') as f:
        text = f.read()
        
    matches = re.findall(
        r'Input:\s*(\[[\s\S]*?\])\s*(\[[\s\S]*?\])\s*Output:\s*(\[[\s\S]*?\])',
        text
    )
    if not matches:
        print("❌ No valid blocks found")
        return

    ops_block, args_block, out_block = matches[0]
    
    ops_block = normalize_list_block(ops_block)
    args_block = normalize_list_block(args_block)
    out_block = normalize_list_block(out_block)
    
    try:
        ops_raw = ast.literal_eval(ops_block)
        args_raw = ast.literal_eval(args_block)
        out_raw = ast.literal_eval(out_block)
    except Exception as e:
        print("❌ Still failed:", e)
        print("--- OPS ---\n", ops_block)
        print("--- ARGS ---\n", args_block)
        print("--- OUT ---\n", out_block)
        return

    operations = [clean_token(op) for op in ops_raw]
    arg_clean = []
    for a in args_raw:
        if a == []:
            arg_clean.append("")
        elif isinstance(a, list):
            arg_clean.append(clean_token(a[0]).lower())
        else:
            arg_clean.append(clean_token(str(a)).lower())

    output = []
    for x in out_raw:
        if x is None:
            output.append("null")
        else:
            output.append(clean_token(str(x)))

    print("Operations:", operations)
    print("Arguments:", arg_clean)
    print("Output:", output)
    return generate_cpp(operations, arg_clean, output)


if __name__ == "__main__":
    print(convert_testcase("testcase.txt"))

