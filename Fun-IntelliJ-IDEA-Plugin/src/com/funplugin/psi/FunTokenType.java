package com.funplugin.psi;

import com.funplugin.FunLanguage;
import com.intellij.psi.tree.IElementType;

/**
 * Created by Pavel on 15.08.2016.
 */
public class FunTokenType extends IElementType {
    public FunTokenType(String debugName){
        super(debugName, FunLanguage.instance);
    }

    @Override
    public String toString() {
        return "FunTokenType." + super.toString();
    }
}
