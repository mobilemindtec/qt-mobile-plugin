package com.qt.plugin.core;

public interface IQtVariant {

    IQtVariant toVariant();

    boolean isVariant();
    boolean isList();
    boolean isMap();
}
