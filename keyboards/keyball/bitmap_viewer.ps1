function Convert-HexToBinary {
    param([string]$hexString)
    $bytes = for ($i = 0; $i -lt $hexString.Length; $i += 2) {
        [Convert]::ToByte($hexString.Substring($i, 2), 16)
    }
    return $bytes
}

function Show-Bitmap {
    param(
        [byte[]]$bytes,
        [int]$startCol = 0
    )
    $result = New-Object string[] 8
    # 상하 반전 표시
    for ($row = 7; $row -ge 0; $row--) {
        $line = " " * $startCol
        foreach ($byte in $bytes) {
            $bit = ($byte -shr (7 - $row)) -band 1
            $line += if ($bit) { "██" } else { "  " }
        }
        $result[7 - $row] = $line
    }
    return $result
}

# Keyball 로고 데이터 (0x80 ~ 0xAF)
$logoLines = @(
    # 첫 번째 줄 (0x80-0x85)
    "000000000000C0F0F88C86C6",
    # 두 번째 줄 (0x90-0x95)
    "000000008000E070786C6464",
    # 세 번째 줄 (0xA0-0xA5)
    "0000003C7F6360E0C0C0C0"
)

$display = New-Object string[] 8
for ($i = 0; $i -lt 8; $i++) {
    $display[$i] = ""
}

Write-Host "=== Keyball 로고 (OLED 표시 형태) ==="
Write-Host

# 각 줄의 비트맵을 생성하고 디스플레이에 추가
for ($i = 0; $i -lt $logoLines.Count; $i++) {
    $bytes = Convert-HexToBinary $logoLines[$i]
    $bitmap = Show-Bitmap $bytes
    
    # 각 줄의 결과를 디스플레이 배열에 추가
    for ($row = 0; $row -lt 8; $row++) {
        $display[$row] = $display[$row] + $bitmap[$row] + "    "
    }
}

# 최종 디스플레이 출력
foreach ($line in $display) {
    Write-Host $line
}
Write-Host 