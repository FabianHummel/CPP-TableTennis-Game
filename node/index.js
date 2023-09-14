const fs = require("fs");

{
    let output = "";
    for (const file of fs.readdirSync("src/ecs/components")) {
        if (file.endsWith(".h") && file !== "index.h") {
            output += `#include "${file}"\n`
        }
    }

    fs.rmSync(`src/ecs/components/index.h`, {force: true});
    fs.writeFileSync(`src/ecs/components/index.h`, output);
}