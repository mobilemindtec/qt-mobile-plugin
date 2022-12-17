package com.qt.plugin.core;

public class QtMobilePluginChannelException extends  RuntimeException{


    public QtMobilePluginChannelException() {
    }

    public QtMobilePluginChannelException(String message) {
        super(message);
    }

    public QtMobilePluginChannelException(String message, Throwable cause) {
        super(message, cause);
    }

    public QtMobilePluginChannelException(Throwable cause) {
        super(cause);
    }

    public QtMobilePluginChannelException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
