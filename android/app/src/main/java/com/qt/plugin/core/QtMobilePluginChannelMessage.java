package com.qt.plugin.core;

import java.util.LinkedList;
import java.util.List;
import java.util.UUID;

public class QtMobilePluginChannelMessage {
    private String id;
    private String channelName;
    private String methodName;
    private Throwable errorObject;
    private boolean error;
    private String errorDescription;

    // c++ to java
    private List<Object> args = new LinkedList<>();

    public QtMobilePluginChannelMessage(){
        this.newId();
    }


    static QtMobilePluginChannelMessage fromError(Throwable errorObject, String errorDescription){
        QtMobilePluginChannelMessage message = new QtMobilePluginChannelMessage();
        message.errorDescription = errorDescription;
        message.error = true;
        message.errorObject = errorObject;
        return message;
    }


    static QtMobilePluginChannelMessage fromArgs(Object ...args){
        QtMobilePluginChannelMessage message = new QtMobilePluginChannelMessage();
        for(Object obj : args)
            message.args.add(obj);

        return message;
    }

    public QtMobilePluginChannelMessage withChannelName(String name){
        this.channelName = name;
        return this;
    }

    public QtMobilePluginChannelMessage withMethodName(String name){
        this.methodName = name;
        return this;
    }

    public QtMobilePluginChannelMessage withMessage(QtMobilePluginChannelMessage message){
        this.methodName = message.getMethodName();
        this.channelName = message.getChannelName();
        this.id = message.getId();
        return this;
    }

    public QtMobilePluginChannelMessage withId(String id){
        this.id = id;
        return this;
    }

    public QtMobilePluginChannelMessage newId(){
        this.id = UUID.randomUUID().toString();
        return this;
    }

    public void addArg(Object arg){
        this.args.add(arg);
    }

    public List<Object> getArgs(){
        return this.args;
    }

    public List<Object> getData(){
        return this.args;
    }

    public Object getFirstData(){
        return this.getArg(0);
    }

    public Object getData(int index){
        return this.getArg(index);
    }

    public <T> T firstArg(){
        return (T) this.getArg(0);
    }

    public <T> T secondArg(){
        return this.getArg(1);
    }

    public <T> T getArg(int index){
        if(index >= 0 && index < this.args.size())
            return (T) this.args.get(index);

        return null;
    }

    public <T> T getArg(int index, T defaultValue){
        if(index >= 0 && index < this.args.size())
            return (T) this.args.get(index);

        return defaultValue;
    }

    public void setId(String id){
        this.id = id;
    }

    public String getId(){
        return this.id;
    }

    public void setChannelName(String channelName){
        this.channelName = channelName;
    }

    public String getChannelName() {
        return this.channelName;
    }

    public void setMethodName(String methodName){
        this.methodName = methodName;
    }

    public String getMethodName() {
        return this.methodName;
    }

    public boolean hasError() {
        return this.error;
    }

    public boolean hasThrowable() {
        return this.errorObject != null;
    }

    public void setThrowable(Throwable errorObject) {
        this.errorObject = errorObject;
    }

    public Throwable getThrowable() {
        return this.errorObject;
    }

    public String getErrorDescription() {
        return this.errorDescription;
    }

    @Override
    public String toString(){
        return channelName + "/" + methodName;
    }

    public String dump() {
        String value = this.toString() + ", ARGS = {";
        for(Object it : args)
            value += it + ", ";

        value += "}, ID = " + id + ", Error = " + error;
        value += ", errorDescription = " + errorDescription + ", errorObject = " + errorObject;
        return value;
    }
}
