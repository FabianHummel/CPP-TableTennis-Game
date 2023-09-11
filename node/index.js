const fs = require("fs");

let output = "";
for (const file of fs.readdirSync("src/components"))
{
    if (file.endsWith(".h") && file !== "index.h")
    {
        output += `#include "${file}"\n`
    }
}

fs.rmSync(`src/components/index.h`, {force: true});
fs.writeFileSync(`src/components/index.h`, output);