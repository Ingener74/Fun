package com.funplugin.psi;

import com.funplugin.FunLanguage;
import com.intellij.psi.tree.IElementType;

/**
 * Created by Pavel on 15.08.2016.
 */
public class FunElementType extends IElementType {
    public FunElementType(String debugName){
        super(debugName, FunLanguage.instance);
    }
}
