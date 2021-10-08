package com.qt.plugin.core;

public class QtChannel {

    protected static native void callback(QtChannelMessage message);

    abstract void callMethod(String methodName, Object[] args...);
}
