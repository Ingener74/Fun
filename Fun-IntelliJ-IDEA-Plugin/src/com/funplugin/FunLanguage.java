package com.funplugin;

import com.intellij.lang.Language;

/**
 * Created by Pavel on 11.08.2016.
 */
public class FunLanguage extends Language {
    public static final FunLanguage instance = new FunLanguage();

    private FunLanguage() {
        super("Fun");
    }
}
