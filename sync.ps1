param(
    [string]$Message = ""
)

Set-Location -Path $PSScriptRoot

if ([string]::IsNullOrWhiteSpace($Message)) {
    $Message = "update: $(Get-Date -Format 'yyyy-MM-dd HH:mm')"
}

Write-Host "==> git add ." -ForegroundColor Cyan
git add .
if ($LASTEXITCODE -ne 0) { Write-Host "git add failed" -ForegroundColor Red; exit 1 }

git commit -m "$Message" | Out-Null
if ($LASTEXITCODE -ne 0) {
    Write-Host "Nothing to commit. Skip push." -ForegroundColor Yellow
    exit 0
}
Write-Host "==> committed: $Message" -ForegroundColor Cyan

Write-Host "==> git push" -ForegroundColor Cyan
git push
if ($LASTEXITCODE -ne 0) {
    Write-Host "git push FAILED. Check network / Clash proxy." -ForegroundColor Red
    exit 1
}

Write-Host "DONE. Visit https://mauthings.github.io/ in a minute." -ForegroundColor Green
