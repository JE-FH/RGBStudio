const HTMLParser = require("node-html-parser");
const fs = require("fs/promises");
const path = require("path");
async function main() {
    if (process.argv.length < 5) {
        throw new Error("Expected 3 argument");
    }

    let target_file_path = path.resolve(process.argv[2]);
    let relative_path = process.argv[4];


    let content = (await fs.readFile(target_file_path)).toString();

    let root = HTMLParser.parse(content);
    await html_element_walker(root, async (htmlElement) => {
        if (htmlElement.tagName == "SCRIPT") {
            if (htmlElement.getAttribute("src") != null) {
                let content = (await fs.readFile(path.join(relative_path, htmlElement.getAttribute("src")))).toString();
                let script_element = new HTMLParser.HTMLElement(
                    "script",
                    {}
                );
                script_element.appendChild(new HTMLParser.TextNode(content, script_element));
                htmlElement.replaceWith(script_element);
            }
        } else if (htmlElement.tagName == "LINK") {
            if (htmlElement.getAttribute("rel") == "stylesheet" && htmlElement.getAttribute("href") != null) {
                let content = (await fs.readFile(path.join(relative_path, htmlElement.getAttribute("href")))).toString();
                let style_element = new HTMLParser.HTMLElement(
                    "style",
                    {}
                );
                style_element.appendChild(new HTMLParser.TextNode(content, style_element));
                htmlElement.replaceWith(style_element);
            }
        }
    });

    await fs.writeFile(process.argv[3], root.innerHTML);
    console.log(`Successfully inlined ${process.argv[3]}`);
}

async function html_element_walker(htmlElement, walker) {
    await walker(htmlElement);
    for (let child of htmlElement.childNodes) {
        await html_element_walker(child, walker);
    }
}

main();