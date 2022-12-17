package com.qt.plugin.core;

import android.app.Activity;
import android.content.Context;

public abstract class QtMobilePluginChannel {

    public abstract void callMethod(QtMobilePluginChannelMessage message);
    public abstract String getChannelName();
    public abstract void register();
    public abstract QtMobilePluginChannelMessage getCurrentMessage();
    private Context context;
    private Activity activity;

    public Activity getActivity() {
        return activity;
    }

    public void setActivity(Activity activity) {
        this.activity = activity;
    }

    public Context getContext() {
        return context;
    }

    public void setContext(Context context) {
        this.context = context;
    }

    protected void sendError(Throwable throwable, String errorDescription){
        QtMobilePluginDispatcher.dispatchError(
            QtMobilePluginChannelMessage.fromError(
                throwable, errorDescription
            ).withMessage(getCurrentMessage())
        );
    }

    protected void sendResult(IQtVariant ...objects){
        QtMobilePluginDispatcher.onResult(
            QtMobilePluginChannelMessage.fromArgs(
                objects
            ).withMessage(getCurrentMessage())
        );
    }

}
