package com.qt.plugin.core;

public class QtChannelMessage {
    public String methodName;
    public Object data;

    public QtChannelMessage(String methodName, Object data){
        this.methodName = methodName;
        this.data = data;
    }
}
