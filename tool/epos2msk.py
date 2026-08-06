#!/usr/bin/env python3

import re
import sys
import argparse


def main():
    aparser = argparse.ArgumentParser(
        prog="Enum to Mask",
        description="What the program does",
        epilog="Text at the bottom of help",
    )

    aparser.add_argument("--depth", required=False)

    args = aparser.parse_args()

    data = sys.stdin.read()
    parser(data, args)


def parser(data, args):
    enum_pattern = re.compile(r"([\s\w\d]*\{)?([\s\w\d,=\/]*)(\}(.*))?")
    match = enum_pattern.search(data)
    clear_data = match[2].strip()

    pattern = re.compile(r"^\s*([\w_\d]+)\s*((=\s*([\d\w]+)))?", flags=re.MULTILINE)
    matches = pattern.finditer(clear_data)

    names = []
    for match_num, match in enumerate(matches, start=1):
        names.append(match.groups()[0])

    common_name = None
    if args.depth:
        common_name = "_".join(names[0].split("_")[: int(args.depth)])

    # print(common_name)

    print("// clang-format off")
    for name in names:
        if name.endswith("_Pos"):
            print(f"#define {name.removesuffix('_Pos')} (1 << {name})")
        elif name.endswith("_Val"):
            # define RCC_CFGR_SW_HSI (RCC_CFGR_SW_HSI_Val << RCC_CFGR_SW_Pos)
            pure_name = name.removesuffix("_Val")
            print(f"#define {pure_name} ({name} << {common_name + '_Pos'})")

    print("// clang-format on")


if __name__ == "__main__":
    main()
    exit(0)
