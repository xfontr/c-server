import { readFile, writeFile } from "fs/promises"
import assert from "node:assert";

/**
 * No try catches.
 * We actually want this to break if anything fails.
 */

//#region Constants
const ERROR_CODE_PREFIX = "ERROR_";
const ERROR_MESSAGE_PREFIX = "ERROR_MSG_"
//#endregion

//#region Paths
const configsPath = "./configs.json";
const errorCodesPath = "./include/constants/error_codes.h";
const errorMessagesPath = "./include/constants/error_messages.h";
const serverConfigsPath = "./include/constants/configs.h";
//#endregion

//#region Template utils
const addQuotes = (content) => typeof content === "string" ? `"${content}"` : content;

const dataRowToConfig = ({ name, content }) => `#define ${name.toLocaleUpperCase()} ${addQuotes(content)}`;

const template = (name, data) => `#ifndef ${name}
#define ${name}

${data}

#endif
`
//#endregion

//#region Errors
const getErrorMessages = (configs) =>
    configs.errors.map(({ name, message }) => ({
        name: `${ERROR_MESSAGE_PREFIX}${name}`,
        content: message,
    }));


const getErrorCodes = (configs) =>
    configs.errors.map(({ name, code }, index) => ({
        name: `${ERROR_CODE_PREFIX}${name}`,
        content: code ?? -index,
    }));
//#endregion

//#region Generate files
const generateErrorCodes = async (data) => {
    assert(typeof data === "string");

    await writeFile(errorCodesPath, template("ERROR_CODES", data));
}

const generateErrorMessages = async (data) => {
    assert(typeof data === "string");

    await writeFile(errorMessagesPath, template("ERROR_MESSAGES", data));
}

const generateServerConfigs = async (data) => {
    assert(typeof data === "string");

    await writeFile(serverConfigsPath, template("CONFIGS", data));
}
//#endregion

const parseConfigs = async () => {
    const rawConfigs = await readFile(configsPath, "utf8");

    const configs = JSON.parse(rawConfigs);

    return configs;
}

const toC = (configs) => ({
    errorCodes: getErrorCodes(configs)
        .map(dataRowToConfig)
        .join("\n"),

    errorMessages: getErrorMessages(configs)
        .map(dataRowToConfig)
        .join("\n"),

    serverConfigs: Object.entries(configs.server)
        .map(([name, content]) => dataRowToConfig({ name, content }))
        .join("\n"),
});

void (async () => {
    const configs = await parseConfigs();

    assert(!!configs?.errors?.length);
    assert(!!configs?.server);

    const {
        errorCodes,
        errorMessages,
        serverConfigs,
    } = toC(configs);

    await generateErrorCodes(errorCodes);
    await generateErrorMessages(errorMessages);
    await generateServerConfigs(serverConfigs);
})();
