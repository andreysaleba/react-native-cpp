#include "JavascriptType.hpp"
#include "DemoModuleImpl.hpp"
#include "JavascriptObject.hpp"
#include "JobDispatcher.hpp"

#include "JobQueueImpl.hpp"

#include <thread>
#include <chrono>

std::shared_ptr<DemoModule> DemoModule::create(const std::shared_ptr<::ReactBridge> &bridge) {
    return std::make_shared<DemoModuleImpl>(bridge);
}

DemoModuleImpl::DemoModuleImpl(const std::shared_ptr<::ReactBridge> &bridge) : mBridge(bridge) {
    mQueue = JobQueueImpl::create();
    mDispatcher = mBridge->createJobDispatcher(mQueue);
    mDispatcher->start();
}

DemoModuleImpl::~DemoModuleImpl() {
    mDispatcher->quit();
}

void DemoModuleImpl::testPromise(const std::shared_ptr<::JavascriptPromise> &promise) {
    promise->resolveString("Success!");
}

void DemoModuleImpl::testCallback(const std::shared_ptr<::JavascriptCallback> &callback) {
    callback->invokeSingleArg(JavascriptObject::fromString("Success"));
}

void DemoModuleImpl::testMap(const std::shared_ptr<::JavascriptMap> &map, const std::shared_ptr<::JavascriptPromise> &promise) {
    auto ret = mBridge->copyMap(map);
    auto simpleMap = mBridge->createMap();
    simpleMap->putBoolean("simple", true);
    simpleMap->putObject("object", JavascriptObject::fromString("Dynamic"));
    ret->putMap("simple", simpleMap);
    promise->resolveMap(ret);
}

void DemoModuleImpl::testArray(const std::shared_ptr<::JavascriptArray> &array, const std::shared_ptr<::JavascriptCallback> &callback) {
    auto ret = mBridge->copyArray(array);
    auto simpleArray = mBridge->createArray();
    simpleArray->pushBoolean(true);
    ret->pushArray(simpleArray);
    auto args = mBridge->createArray();
    args->pushArray(ret);
    args->pushObject(JavascriptObject::fromString("Dynamic"));
    callback->invokeSingleArg(JavascriptObject::fromArray(args));
}

void DemoModuleImpl::testBool(bool value, const std::shared_ptr<::JavascriptPromise> &promise) {
    promise->resolveBoolean(value);
}

void
DemoModuleImpl::testPrimitives(int32_t i, double d, const std::shared_ptr<::JavascriptCallback> &callback) {
    callback->invoke(std::vector<std::shared_ptr<JavascriptObject>> {JavascriptObject::fromInt(i), JavascriptObject::fromDouble(d)});
}

void DemoModuleImpl::testString(const std::string &value, const std::shared_ptr<::JavascriptPromise> &promise) {
    promise->resolveObject(JavascriptObject::fromString("Success!"));
}

void DemoModuleImpl::testEventWithArray(const std::shared_ptr<::JavascriptArray> & value) {
    auto param = mBridge->copyArray(value);
    mBridge->emitEventWithArray(EVENT_NAME, param);
}

void DemoModuleImpl::testEventWithMap(const std::shared_ptr<::JavascriptMap> & value) {
    std::thread t([=]() {
        for (int i = 5; i > 0; --i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            mQueue->enqueue([=]() {
                auto ret = mBridge->createMap();
                ret->putInt("i", i);
                mBridge->emitEventWithMap(EVENT_NAME, ret);
            });
        }
    });
    t.detach();
}
