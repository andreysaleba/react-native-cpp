#include "DemoModule.hpp"

class JobQueueImpl;
class JobDispatcher;

class DemoModuleImpl : public DemoModule {
public:
    static std::shared_ptr<DemoModule> create(const std::shared_ptr<::ReactBridge> & bridge);
    DemoModuleImpl(const std::shared_ptr<::ReactBridge> & bridge);
    ~DemoModuleImpl();

    void testPromise(const std::shared_ptr<::JavascriptPromise> & promise) override;
    void testCallback(const std::shared_ptr<::JavascriptCallback> & callback) override;
    void testMap(const std::shared_ptr<::JavascriptMap> & map, const std::shared_ptr<::JavascriptPromise> & promise) override;
    void testArray(const std::shared_ptr<::JavascriptArray> & array, const std::shared_ptr<::JavascriptCallback> & callback) override;
    void testBool(bool value, const std::shared_ptr<::JavascriptPromise> & promise) override;
    void testPrimitives(int32_t i, double d, const std::shared_ptr<::JavascriptCallback> & callback) override;
    void testString(const std::string & value, const std::shared_ptr<::JavascriptPromise> & promise) override;
    void testEventWithArray(const std::shared_ptr<::JavascriptArray> & value) override;
    void testEventWithMap(const std::shared_ptr<::JavascriptMap> & value) override;

private:
    std::shared_ptr<ReactBridge> mBridge;
    std::shared_ptr<JobQueueImpl> mQueue;
    std::shared_ptr<JobDispatcher> mDispatcher;
};
