def print_bitmap(hex_str):
    # 16진수 문자열을 바이트 배열로 변환
    bytes_array = [int(hex_str[i:i+2], 16) for i in range(0, len(hex_str), 2)]
    
    # 8x8 비트맵 출력
    for row in range(8):
        line = ""
        for byte in bytes_array:
            bit = (byte >> (7 - row)) & 1
            line += "██" if bit else "  "
        print(line)

# 로고 데이터 (각 줄은 6바이트)
logo_data = [
    "000000000000C0F0F88C86C6",  # 0x80-0x85
    "000000008000E070786C6464",  # 0x90-0x95
    "0000003C7F6360E0C0C0C0"     # 0xA0-0xA5
]

print("Keyball 로고 비트맵 시각화:")
for i, data in enumerate(logo_data):
    print(f"\n섹션 {i+1}/3:")
    print_bitmap(data) 