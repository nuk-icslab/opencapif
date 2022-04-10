const assert = require('assert');
const capifInvk = require('../index');

const PromiseFail = async (proms) => await assertPromise(proms, false);
const PromiseSucced = async (proms) => await assertPromise(proms);
const assertPromise = async (prom, succed = true) => {
    succed = succed ? true : false;
    try {
        prom = Array.isArray(prom) ? prom : [prom];
        await Promise.all(prom);
        assert.strictEqual(true, succed);
    }
    catch (ex) { assert.notStrictEqual(true, succed, ex); }
}

describe('CAPIF API Invoker', function () {
    describe('onboardInvoker()', function () {
        it('should return Invoker ID fetched from CCF', async function () {
            await PromiseSucced(capifInvk.onboardInvoker())
        });
    });
});
