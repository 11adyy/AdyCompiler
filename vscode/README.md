
# APL (Ady) — VS Code Extension
## Quick install
```bash
npm install
npm run build
vsce package
```

## Docker
```bash
docker build -t apl-extension .
docker run --rm -v $(pwd)/output:/output apl-extension
```
