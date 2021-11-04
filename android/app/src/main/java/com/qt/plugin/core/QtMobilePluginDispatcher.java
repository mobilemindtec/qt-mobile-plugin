package com.qt.plugin.core;

import android.util.Log;

import java.util.HashMap;
import java.util.Map;

public class QtMobilePluginDispatcher {

    static String TAG = "QtMobilePluginDispatcher";
    private static Map<String, QtMobilePluginChannel> CHANNELS = new HashMap<>();
    private QtMobilePluginChannelMessage currentMessage;

    public static native void onResult(QtMobilePluginChannelMessage message);

    public static void channelRegister(String channelName, QtMobilePluginChannel channel){
        Log.i(TAG, "channel register " + channelName);
        if(!CHANNELS.containsKey(channelName)){
            CHANNELS.put(channelName, channel);
        }
    }

    public void dispatch(QtMobilePluginChannelMessage message){

        this.currentMessage = currentMessage;
        Log.i(TAG, "dispatch channel " + message.getChannelName());

        QtMobilePluginChannel channel = null;
        for(String availableChannel : CHANNELS.keySet()){
            if(availableChannel.equals(message.getChannelName())){
                channel = CHANNELS.get(availableChannel);
            }
        }

        if(channel != null){
            try {
                channel.callMethod(message);
            }catch (QtMobilePluginChannelException ex){
                dispatchError(null, ex.getMessage(), message);
            }catch (Exception ex){
                Log.e(TAG, "Error execute method", ex);
                dispatchError(
                        ex,
                        String.format(
                                "Ocorreu um erro desconhecido. Channel %s/%s: %s",
                                message.getChannelName(),
                                message.getMethodName(),
                                ex.getMessage()),
                        message);
            }
        } else {
            Log.i(TAG, "channel not found: " + message.getChannelName());
            dispatchError(
                    null,
                    "channel " + message.getChannelName() + " not available",
                    message);
        }

    }

    public static void dispatchError(Throwable throwable, String errorDescription, QtMobilePluginChannelMessage message){
        QtMobilePluginDispatcher.onResult(
                QtMobilePluginChannelMessage.fromError(
                        throwable, errorDescription
                ).withMessage(message)
        );
    }

    public static void dispatchError(QtMobilePluginChannelMessage message){
        QtMobilePluginDispatcher.onResult(message);
    }

}
