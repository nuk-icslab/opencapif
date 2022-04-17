const assert = require('assert');
const expect = require('chai').expect;
const sinon = require('sinon');
const { capifAef } = require('../index');

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

describe('Express middleware of CAPIF AEF', function () {
    let mw;
    let req = {
        originalUrl: 'test-api/v1/resource/test',
        method: 'GET'
    };
    let res = {
        end: () => { },
        statusCode: 200
    };
    let nextSpy;

    beforeEach(function () {
        mw = capifAef('test');
        nextSpy = sinon.spy();
    });
    describe('request handler creation', function () {

        it('should return a function()', function () {
            expect(mw).to.be.a('function');
        });

        it('should accept three arguments', function () {
            expect(mw.length).to.equal(3);
        });
    });

    describe('request handler calling', function () {
        it('should call next() once', function () {
            mw(req, res, nextSpy);
            res.end();
            expect(nextSpy.calledOnce).to.be.true;
        });
    });

});
