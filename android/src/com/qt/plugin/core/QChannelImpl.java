package com.qt.plugin.core;

import java.util.Map;

public abstract class QtChannelImpl extends QtChannel {

    private final String ChannelName = "com.qt.plugin.QtChannel";
    private static Map<String, QtChannel> CHANNELS = HashMap<>();


    public QtChannelImpl(){
        register();
    }

    public void register(){
        channelRegister(ChannelName, this);
    }

    public String getChannelName(){
        return this.ChannelName;
    }

    public void callMethod(QtChannelMessage message){

        QtChannel channel = null;
        for(String availableChannel : CHANNELS){
            if(availableChannel.equals(channelName)){
                channel = CHANNELS.get(availableChannel);
            }
        }

        if(channel != null){
            channel.callMethod(message);
        } else {
            sendError("channel " + channelName " not available", methodName);
        }

    }

    public void callMethod(String channelName, String methodName, Object[] args...){

       QtChannelMessage message = QtChannelMessage.fromArgs(args...)
           .withChannelName(channelName)
           .withMethodName(methodName);
       this.callMethod(message);
    }



}
