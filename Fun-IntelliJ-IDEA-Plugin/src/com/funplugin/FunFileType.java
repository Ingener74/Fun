package com.funplugin;

import com.intellij.openapi.fileTypes.LanguageFileType;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;

/**
 * Created by Pavel on 13.08.2016.
 */
public class FunFileType extends LanguageFileType {
    public static final FunFileType instance = new FunFileType();
    private FunFileType(){
        super(FunLanguage.instance);
    }

    @NotNull
    @Override
    public String getName() {
        return "Fun file";
    }

    @NotNull
    @Override
    public String getDescription() {
        return "Fun language file";
    }

    @NotNull
    @Override
    public String getDefaultExtension() {
        return "fun";
    }

    @Nullable
    @Override
    public Icon getIcon() {
        return FunIcons.FILE;
    }
}
