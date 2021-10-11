package com.qt.plugin.core;

import java.util.Map;

public abstract class QtChannel {

    protected static native void callback(QtChannelMessage message);

    protected abstract void callMethod(String methodName, QtChannelMessage message);
    public abstract void register();
    public abstract String getChannelName();

    protected void sendError(Throwable throwable, String errorDescription, String methodName){
        callback(
            QtChannelMessage.fromError(
                throwable, errorDescription
            )
            .withChannelName(this.getChannelName())
            .withMethodName(methodName)
        );
    }

    protected void sendError(Throwable throwable, String errorDescription, QtChannelMessage message){
        callback(
            QtChannelMessage.fromError(
                throwable, errorDescription
            )
            .withChannelName(message.getChannelName())
            .withMethodName(message.getMethodName())
        );
    }

    protected void sendError(String errorDescription, String methodName){
        callback(
            QtChannelMessage.fromError(
                throwable, errorDescription
            )
            .withChannelName(this.getChannelName())
            .withMethodName(methodName)
        );
    }

    protected void sendError(String errorDescription, QtChannelMessage message){
        callback(
            QtChannelMessage.fromError(
                throwable, errorDescription
            )
            .withChannelName(message.getChannelName())
            .withMethodName(message.getMethodName())
        );
    }

    protected void sendData(Object object, String methodName){
        callback(
            QtChannelMessage.fromData(
                object
            )
            .withChannelName(this.getChannelName())
            .withMethodName(methodName)
        );
    }

    protected void sendData(QtChannelMessage request, Object args...){
        callback(
            QtChannelMessage.fromArgs(
                args...
            )
            .withChannelName(this.getChannelName())
            .withMethodName(request.getMethodNate())
        );

    }

}
