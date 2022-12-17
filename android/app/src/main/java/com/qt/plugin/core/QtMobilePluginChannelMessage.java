package com.qt.plugin.core;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;
import java.util.UUID;

public class QtMobilePluginChannelMessage implements Serializable {
    private String id;
    private String channelName;
    private String methodName;
    private boolean error;
    private String errorDescription;
    private Throwable errorObject;

    // c++ to java
    private QtVariantList values = new QtVariantList();

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


    static QtMobilePluginChannelMessage fromArgs(IQtVariant ...args){
        QtMobilePluginChannelMessage message = new QtMobilePluginChannelMessage();
        for(IQtVariant obj : args)
            message.addVariant(obj);

        return message;
    }

    public void addVariant(Object value){
        this.values.add(new QtVariant(value));
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

    public void addArg(QtVariant arg){
        this.values.add(arg);
    }

    public List<IQtVariant> getArgs(){
        return this.values;
    }

    public List<IQtVariant> getData(){
        return this.values;
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
        if(index >= 0 && index < this.values.size()) {

            IQtVariant variant = this.values.get(index);

            if(variant.isVariant()){
                return  ((QtVariant)variant).<T>getValue();
            }

            return (T) this.values.get(index);
        }

        return null;
    }

    public <T> T getArg(int index, T defaultValue){
        if(index >= 0 && index < this.values.size()) {
            IQtVariant variant = this.values.get(index);

            if(variant.isVariant()){
                T val =  ((QtVariant)variant).<T>getValue();
                return val != null ? val : defaultValue;
            }

            return (T) this.values.get(index);
        }
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
        for(Object it : values)
            value += it + ", ";

        value += "}, ID = " + id + ", Error = " + error;
        value += ", errorDescription = " + errorDescription + ", errorObject = " + errorObject;
        return value;
    }
}
