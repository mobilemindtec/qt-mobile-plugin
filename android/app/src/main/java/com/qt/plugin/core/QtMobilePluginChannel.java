package com.qt.plugin.core;

public abstract class QtMobilePluginChannel {

    public abstract void callMethod(QtMobilePluginChannelMessage message);
    public abstract String getChannelName();
    public abstract void register();
    public abstract QtMobilePluginChannelMessage getCurrentMessage();

    protected void sendError(Throwable throwable, String errorDescription){
        QtMobilePluginDispatcher.dispatchError(
            QtMobilePluginChannelMessage.fromError(
                throwable, errorDescription
            ).withMessage(getCurrentMessage())
        );
    }

    protected void sendResult(Object ...objects){
        QtMobilePluginDispatcher.onResult(
            QtMobilePluginChannelMessage.fromArgs(
                objects
            ).withMessage(getCurrentMessage())
        );
    }

}
