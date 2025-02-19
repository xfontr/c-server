import assert from "node:assert";

const options = {
    requests: 15,
}

const request = async (i) => {
    try {
        console.log("Request number: ", i);
        await fetch("https://127.0.0.1:8080");
    } catch (_) {
        // no-op
    }
}

const getRequestStack = (size) => {
    assert(!isNaN(size));

    return (new Array(size).fill(0)).map(request);
}


void (async () => {
    Promise.all(getRequestStack(options.requests))
})();