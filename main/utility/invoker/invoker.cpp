#include "invoker.hpp"
#include "../memory/signatures/signatures.hpp"
#include "hashmap.hpp"
#include "../logger/logger.hpp"

static Invoker* invokerInstance = nullptr;

Invoker* Invoker::Instance() {
    if (!invokerInstance) {
        invokerInstance = new Invoker();
    }

    return invokerInstance;
}

void Invoker::Uninitialize() {
    invokerInstance = nullptr;
    delete this;
}

NativeCallContext::NativeCallContext() {
	returnValue = &returnStack[0];
	arguments = &argumentStack[0];
}

Handler Invoker::GetHandler(scrNativeHash hash) {
	return (Handler)(Signatures::Instance()->definitions.getNativeAddressFromHash(hash));
}

void Invoker::Begin() {
    callContext.Reset();
}

void Invoker::End(scrNativeHash hash) {
    Handler handler = GetHandler(hash);
    handler(&callContext);
}

void Invoker::Dump() {
    std::ofstream file("C:\\Entrypoints\\hashes.txt"); // replace
    
    uintptr_t base = (uintptr_t)GetModuleHandleA("rdr2.exe");
    for (auto native : hashmap) {
        uintptr_t address = (Signatures::Instance()->definitions.getNativeAddressFromHash(native.second) - base);
        file << std::hex << "0x" << native.second << " : " << std::hex << "0x" << address << " //" << native.first << "\n";
    }

    file.close();
}