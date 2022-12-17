package com.qt.plugin.core;

import java.util.LinkedList;
import java.util.List;

public class QtVariantList extends LinkedList<IQtVariant> implements IQtVariant{

    public static QtVariantList from(List list){
        QtVariantList result = new QtVariantList();
        for(Object it : list){
            result.addValue(it);
        }
        return result;
    }

    public void addValue(Object value){
        super.add(QtVariant.from(value));
    }

    @Override
    public IQtVariant toVariant() {
        return this;
    }

    @Override
    public boolean isVariant() {
        return false;
    }

    @Override
    public boolean isList() {
        return true;
    }

    @Override
    public boolean isMap() {
        return false;
    }

    public List toList(){
        return QtVariantConverter.toList(this);
    }
}
