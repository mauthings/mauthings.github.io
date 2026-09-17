# ==============================================================
# sync.ps1 — 一键将本地修改推送到 GitHub
# 用法：
#   1) 在仓库根目录（即 academic-homepage）下，右键 → "使用 PowerShell 运行"
#   2) 或在终端中执行：  .\sync.ps1 "本次提交说明"
#
# 脚本会依次执行：
#   git add .  →  git commit  →  git push
# 若无改动可提交，git commit 会以非零退出；脚本会打印提示并不报错退出。
# ==============================================================

param(
    [string]$Message = ""
)

# 进入脚本所在目录（即仓库根）
Set-Location -Path $PSScriptRoot

# 如未传 commit 信息，使用默认时间戳
if ([string]::IsNullOrWhiteSpace($Message)) {
    $Message = "update: $(Get-Date -Format 'yyyy-MM-dd HH:mm')"
}

Write-Host "==> git add ." -ForegroundColor Cyan
git add .
if ($LASTEXITCODE -ne 0) { Write-Host "git add 失败" -ForegroundColor Red; exit 1 }

Write-Host "==> git commit -m `"$Message`"" -ForegroundColor Cyan
git commit -m "$Message"
$commitCode = $LASTEXITCODE

# 22 = nothing to commit（这是 Git 的 "nothing to commit" 退出码，Windows 上为 1）
if ($commitCode -ne 0) {
    Write-Host "本次无新改动需要提交，跳过 push。" -ForegroundColor Yellow
    exit 0
}

Write-Host "==> git push" -ForegroundColor Cyan
git push
if ($LASTEXITCODE -ne 0) {
    Write-Host "git push 失败，请检查网络 / 凭据 / 分支" -ForegroundColor Red
    exit 1
}

Write-Host "✓ 同步完成：$Message" -ForegroundColor Green
Write-Host "  几秒后访问 https://mauthings.github.io/ 即可看到更新。" -ForegroundColor Green