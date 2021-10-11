package com.qt.plugin.core;

public class QtChannelMessage {
    private String id;
    private String channelName;
    private String methodName;
    private Throwable errorObject;
    private boolean error;
    private String errorDescription;

    // c++ to java
    private List<Object> args = new LinkedList<>();

    public QtChannelMessage(){}


    static QtChannelMessage fromError(Throwable errorObject, String errorDescription){
        QtChannelMessage message = new QtChannelMessage();
        message.errorDescription = errorDescription;
        message.error = true;
        message.errorObject = errorObject;
        return message;
    }


    static QtChannelMessage fromArgs(Object args...){
        QtChannelMessage message = new QtChannelMessage();
        for(Object ojb : args)
            message.args.add(obj);
        return message;
    }

    public QtChannelMessage withChannelName(String name){
        this.channelName = name;
        return this;
    }

    public QtChannelMessage withMethodName(String name){
        this.methodName = name;
        return this;
    }

    public addArg(Object arg){
        this.args.add(arg);
        return this;
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

    public T <T> firstArg(){
        return this.getArg(0);
    }

    public <T> T secondArg(){
        return this.getArg(1);
    }

    public <T> T getArg(int index){
        if(index >= 0 && index < this.args.size())
            return this.args[index];

        return null;
    }

    public void setId(String id){
        this.id = id;
    }

    public String getId(){
        return this.id;
    }

    public String getChannelName() {
        return this.channelName;
    }

    public String getMethodName() {
        return this.methodName;
    }

    public Object getData() {
        return this.data;
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

    String toString(){
        return channelName + "/" + methodName;
    }

    String dump() {
        String value = this.toString() + ", ARGS = {";
        for(Object it : args)
            value += it + ", ";

        value += "}, ID = " + id + ", Error = " + error;
        value += ", errorDescription = " + errorDescription + ", errorObject = " + errorObject;
        return value;
    }
}
