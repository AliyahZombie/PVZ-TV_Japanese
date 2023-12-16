package com.transmension.mobile;

import android.animation.LayoutTransition;
import android.animation.ObjectAnimator;
import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.RoundRectShape;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.preference.PreferenceManager;
import android.text.Editable;
import android.text.InputFilter;
import android.text.InputType;
import android.text.TextWatcher;
import android.util.Pair;
import android.util.TypedValue;
import android.util.Xml;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.HorizontalScrollView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.NumberPicker;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.trans.pvz.R;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Locale;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

public class SetActivity extends Activity {

    public void loadPreferencesFromAssetsFile(SharedPreferences preferences, SharedPreferences sharedPreferences) {
        //如果是初次启动，则载入assets文件夹中的data.xml
        if (preferences.getBoolean("firstLaunch", true)) {
            try {
                InputStream inputStream = getAssets().open("data.xml");
                if (inputStream != null) {
                    XmlPullParser parser = Xml.newPullParser();
                    parser.setInput(inputStream, "utf-8");

                    int eventType = parser.getEventType();
                    SharedPreferences.Editor editor = sharedPreferences.edit();
                    while (eventType != XmlPullParser.END_DOCUMENT) {
                        if (eventType == XmlPullParser.START_TAG) {
                            switch (parser.getName()) {
                                case "boolean": {
                                    String name = parser.getAttributeValue(null, "name");
                                    boolean value = Boolean.parseBoolean(parser.getAttributeValue(null, "value"));
                                    editor.putBoolean(name, value);
                                    break;
                                }
                                case "int": {
                                    String name = parser.getAttributeValue(null, "name");
                                    int value = Integer.parseInt(parser.getAttributeValue(null, "value"));
                                    editor.putInt(name, value);
                                    break;
                                }
                            }
                        }
                        eventType = parser.next();
                    }
                    editor.apply();
                    inputStream.close();
                }
            } catch (IOException | XmlPullParserException e) {
                e.printStackTrace();
            }
            preferences.edit().putBoolean("firstLaunch", false).apply();
        }
    }

    public static File getUserDataFile(Context context) {
        SharedPreferences sharedPreferences = context.getSharedPreferences("data", 0);
        if (sharedPreferences.getBoolean("useExternalPath", Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)) {
            return context.getExternalFilesDir(null);
        } else {
            return context.getFilesDir();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        //设置主题、导航栏与操作栏透明，UI会好看些

        boolean isNight = (getResources().getConfiguration().uiMode & Configuration.UI_MODE_NIGHT_YES) == Configuration.UI_MODE_NIGHT_YES;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH)
            setTheme(isNight ? android.R.style.Theme_DeviceDefault : android.R.style.Theme_DeviceDefault_Light);
        Window window = getWindow();
        if (!isNight) {
            window.getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LIGHT_STATUS_BAR | View.SYSTEM_UI_FLAG_LIGHT_NAVIGATION_BAR);
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q)
            window.setNavigationBarContrastEnforced(false);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            window.setStatusBarColor(Color.TRANSPARENT);
            window.setNavigationBarColor(Color.TRANSPARENT);
        }
        ActionBar actionBar = getActionBar();
        if (actionBar != null) {
            actionBar.setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        }


        //如果是初次启动，则载入assets文件夹中的data.xml
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this);
        SharedPreferences sharedPreferences = getSharedPreferences("data", 0);

        loadPreferencesFromAssetsFile(preferences, sharedPreferences);


        setTitle(getString(R.string.addon_title));
        ScrollView scrollView = new ScrollView(this);
        LinearLayout linearLayout = new LinearLayout(this);
        linearLayout.setOrientation(LinearLayout.VERTICAL);
        LayoutTransition transition = new LayoutTransition();
        transition.setDuration(200L);
        ObjectAnimator animator = ObjectAnimator.ofFloat(null, "scaleX", 0.0f, 1.0f);
        transition.setAnimator(2, animator);
        linearLayout.setLayoutTransition(transition);


        LinearLayout.LayoutParams wrapWrapParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        wrapWrapParams.gravity = Gravity.CENTER;
        LinearLayout.LayoutParams matchWrapParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        matchWrapParams.gravity = Gravity.CENTER;
        LinearLayout.LayoutParams weightParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        weightParams.weight = 1;
        LinearLayout.LayoutParams marginParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        marginParams.setMargins(0, 20, 0, 20);

        float density = getResources().getDisplayMetrics().density;
        float radius = 40 * density;
        ShapeDrawable oval = new ShapeDrawable(new RoundRectShape(new float[]{radius, radius, radius, radius, radius, radius, radius, radius}, null, null));
        oval.getPaint().setColor(isNight ? Color.DKGRAY : Color.LTGRAY);


        String aspectName = getString(R.string.addon_aspect_name);
        Button aspectExpand = new Button(this);
        LinearLayout aspectLayout = new LinearLayout(this);

        aspectExpand.setText(String.format("▽ %s ▽", aspectName));
        aspectExpand.setTypeface(Typeface.DEFAULT_BOLD);
        aspectExpand.setTextSize(15f);
        aspectExpand.setBackgroundDrawable(oval);
        aspectExpand.setLayoutParams(marginParams);
        aspectExpand.setOnClickListener(view -> {
            boolean isVisible = aspectLayout.getVisibility() == View.VISIBLE;
            ((Button) view).setText(isVisible ? String.format("▽ %s ▽", aspectName) : String.format("△ %s △", aspectName));
            aspectLayout.setVisibility(isVisible ? View.GONE : View.VISIBLE);
        });
        TextView aspectInfo = new TextView(this);
        aspectInfo.setGravity(Gravity.CENTER);
        aspectInfo.setText(R.string.addon_aspect_info);
        aspectInfo.setTextSize(15f);

        CheckBox fullscreenCheckBox = new CheckBox(this);
        fullscreenCheckBox.setText(R.string.addon_aspect_fullscreen);
        fullscreenCheckBox.setTextSize(16f);
        fullscreenCheckBox.setPadding(0, 30, 0, 30);
        fullscreenCheckBox.setChecked(!sharedPreferences.getBoolean("shiLiuBiJiu", true));
        fullscreenCheckBox.setLayoutParams(wrapWrapParams);

        String fullscreenText1 = getString(R.string.addon_aspect_fullscreen_text1);
        String fullscreenText2 = getString(R.string.addon_aspect_fullscreen_text2);
        TextView fullscreenInfo = new TextView(this);
        fullscreenInfo.setGravity(Gravity.CENTER);
        fullscreenInfo.setText(fullscreenCheckBox.isChecked() ? fullscreenText1 : fullscreenText2);
        fullscreenInfo.setTextSize(15f);


        LinearLayout aspectChooser = new LinearLayout(this);
        aspectChooser.setOrientation(LinearLayout.HORIZONTAL);

        NumberPicker widthPicker = new NumberPicker(this);
        widthPicker.setMaxValue(20);
        widthPicker.setMinValue(1);
        widthPicker.setLayoutParams(weightParams);
        widthPicker.setValue(sharedPreferences.getInt("width", 16));
        NumberPicker heightPicker = new NumberPicker(this);
        heightPicker.setMaxValue(20);
        heightPicker.setMinValue(1);
        heightPicker.setLayoutParams(weightParams);
        heightPicker.setValue(sharedPreferences.getInt("height", 9));
        aspectChooser.addView(widthPicker);
        aspectChooser.addView(heightPicker);
        aspectChooser.setVisibility(fullscreenCheckBox.isChecked() ? View.GONE : View.VISIBLE);
        fullscreenCheckBox.setOnCheckedChangeListener((compoundButton, b) -> {
            aspectChooser.setVisibility(b ? View.GONE : View.VISIBLE);
            fullscreenInfo.setText(b ? fullscreenText1 : fullscreenText2);
        });

        LinearLayout container2 = new LinearLayout(this);
        container2.setOrientation(LinearLayout.HORIZONTAL);
        TextView textView2 = new TextView(this);
        textView2.setGravity(Gravity.CENTER);
        textView2.setText(R.string.addon_aspect_scale);
        textView2.setTextSize(16f);
        textView2.setTextColor(isNight ? Color.WHITE : Color.BLACK);
        textView2.setLayoutParams(weightParams);
        SeekBar scaleSeekBar = new SeekBar(this);
        scaleSeekBar.setMax(20);
        scaleSeekBar.setProgress(sharedPreferences.getInt("scaleX", 0));
        scaleSeekBar.setLayoutParams(matchWrapParams);
        InputFilter[] filters2 = new InputFilter[1];
        filters2[0] = new InputFilter.LengthFilter(2);
        EditText editText2 = new EditText(this);
        editText2.setText(String.valueOf(sharedPreferences.getInt("scaleX", 0)));
        scaleSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                editText2.setText(String.valueOf(i));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });
        editText2.setHint("(0-20)");
        editText2.setGravity(Gravity.CENTER);
        editText2.setInputType(InputType.TYPE_CLASS_NUMBER);
        editText2.setFilters(filters2);
        editText2.setSelectAllOnFocus(true);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN)
            editText2.setBackground(null);
        editText2.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                if (charSequence == null || charSequence.length() == 0) return;
                int num = Integer.parseInt(String.valueOf(charSequence));
                scaleSeekBar.setProgress(Math.min(num, 20));
            }

            @Override
            public void afterTextChanged(Editable editable) {
            }
        });
        container2.addView(textView2);
        container2.addView(editText2);

        TextView scaleInfo = new TextView(this);
        scaleInfo.setGravity(Gravity.CENTER);
        scaleInfo.setText(R.string.addon_aspect_scale_info);
        scaleInfo.setTextSize(15f);
        scaleInfo.setPadding(0, 20, 0, 20);

        Button saveAspect = new Button(this);
        saveAspect.setText(R.string.addon_aspect_save);
        saveAspect.setOnClickListener(view -> {
            sharedPreferences.edit().putInt("width", widthPicker.getValue()).putInt("height", heightPicker.getValue()).putInt("scaleX", scaleSeekBar.getProgress()).putInt("scaleY", scaleSeekBar.getProgress()).putBoolean("shiLiuBiJiu", !fullscreenCheckBox.isChecked()).apply();
            Toast.makeText(SetActivity.this, getString(R.string.addon_aspect_toast1) + (fullscreenCheckBox.isChecked() ? getString(R.string.addon_aspect_toast2) : String.format(Locale.getDefault(), "%d: %d", widthPicker.getValue(), heightPicker.getValue())) + String.format(Locale.getDefault(), getString(R.string.addon_aspect_toast3), scaleSeekBar.getProgress()), Toast.LENGTH_SHORT).show();
        });
        aspectLayout.setVisibility(View.GONE);
        aspectLayout.setOrientation(LinearLayout.VERTICAL);
        aspectLayout.setLayoutTransition(transition);
        aspectLayout.addView(aspectInfo);
        aspectLayout.addView(fullscreenCheckBox);
        aspectLayout.addView(fullscreenInfo);
        aspectLayout.addView(aspectChooser);
        aspectLayout.addView(container2);
        aspectLayout.addView(scaleSeekBar);
        aspectLayout.addView(scaleInfo);
        aspectLayout.addView(saveAspect);


        String keyboardName = getString(R.string.addon_keyboard_name);
        Button keyboardExpand = new Button(this);
        LinearLayout keyboardLayout = new LinearLayout(this);

        keyboardExpand.setText(String.format("▽ %s ▽", keyboardName));
        keyboardExpand.setTypeface(Typeface.DEFAULT_BOLD);
        keyboardExpand.setTextSize(15f);
        keyboardExpand.setBackgroundDrawable(oval);
        keyboardExpand.setLayoutParams(marginParams);
        keyboardExpand.setOnClickListener(view -> {
            boolean isVisible = keyboardLayout.getVisibility() == View.VISIBLE;
            ((Button) view).setText(isVisible ? String.format("▽ %s ▽", keyboardName) : String.format("△ %s △", keyboardName));
            keyboardLayout.setVisibility(isVisible ? View.GONE : View.VISIBLE);
        });

        TextView keyboardInfo = new TextView(this);
        keyboardInfo.setGravity(Gravity.CENTER);
        keyboardInfo.setText(R.string.addon_keyboard_info);
        keyboardInfo.setTextSize(15f);


        CheckBox useKeyboard = new CheckBox(this);
        useKeyboard.setChecked(sharedPreferences.getBoolean("useInGameKeyboard", true));
        useKeyboard.setText(R.string.addon_keyboard_usekeyboard);
        useKeyboard.setTextSize(16f);
        useKeyboard.setOnCheckedChangeListener((compoundButton, b) -> sharedPreferences.edit().putBoolean("useInGameKeyboard", b).apply());
        useKeyboard.setPadding(0, 30, 0, 30);
        useKeyboard.setLayoutParams(wrapWrapParams);
        TextView useKeyboardInfo = new TextView(this);
        useKeyboardInfo.setGravity(Gravity.CENTER);
        useKeyboardInfo.setText(R.string.addon_keyboard_usekeyboard_info);
        useKeyboardInfo.setTextSize(15f);


        CheckBox useSpecialPause = new CheckBox(this);
        useSpecialPause.setText(R.string.addon_keyboard_specialpause);
        useSpecialPause.setTextSize(16f);
        useSpecialPause.setPadding(0, 30, 0, 30);
        useSpecialPause.setChecked(sharedPreferences.getBoolean("useSpecialPause", false));
        useSpecialPause.setOnCheckedChangeListener((compoundButton, b) -> sharedPreferences.edit().putBoolean("useSpecialPause", b).apply());
        useSpecialPause.setLayoutParams(wrapWrapParams);
        TextView specialPauseInfo = new TextView(this);
        specialPauseInfo.setGravity(Gravity.CENTER);
        specialPauseInfo.setText(R.string.addon_keyboard_specialpause_info);
        specialPauseInfo.setTextSize(15f);


        CheckBox lockButtonPosition = new CheckBox(this);
        lockButtonPosition.setChecked(sharedPreferences.getBoolean("isVisibilityLockPosition", false));
        lockButtonPosition.setText(R.string.addon_keyboard_lock);
        lockButtonPosition.setTextSize(16f);
        lockButtonPosition.setOnCheckedChangeListener((compoundButton, b) -> sharedPreferences.edit().putBoolean("isVisibilityLockPosition", b).apply());
        lockButtonPosition.setPadding(0, 30, 0, 30);
        lockButtonPosition.setLayoutParams(wrapWrapParams);
        TextView lockInfo = new TextView(this);
        lockInfo.setGravity(Gravity.CENTER);
        lockInfo.setText(R.string.addon_keyboard_lock_info);
        lockInfo.setTextSize(15f);


        LinearLayout container1 = new LinearLayout(this);
        container1.setOrientation(LinearLayout.HORIZONTAL);
        TextView textView = new TextView(this);
        textView.setGravity(Gravity.CENTER);
        textView.setText(R.string.addon_keyboard_longpress);
        textView.setTextSize(16f);
        textView.setTextColor(isNight ? Color.WHITE : Color.BLACK);
        textView.setLayoutParams(weightParams);
        SeekBar seekBar = new SeekBar(this);
        seekBar.setMax(20);
        seekBar.setProgress(sharedPreferences.getInt("longPress", 8));
        seekBar.setLayoutParams(matchWrapParams);
        InputFilter[] filters1 = new InputFilter[1];
        filters1[0] = new InputFilter.LengthFilter(2);
        EditText editText = new EditText(this);
        editText.setText(String.valueOf(sharedPreferences.getInt("longPress", 8)));
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                if (i == 0) {
                    seekBar.setProgress(1);
                    return;
                }
                editText.setText(String.valueOf(i));
                sharedPreferences.edit().putInt("longPress", i).apply();
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });
        editText.setHint("(1-20)");
        editText.setGravity(Gravity.CENTER);
        editText.setInputType(InputType.TYPE_CLASS_NUMBER);
        editText.setFilters(filters1);
        editText.setSelectAllOnFocus(true);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN)
            editText.setBackground(null);
        editText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                if (charSequence == null || charSequence.length() == 0) return;
                int num = Integer.parseInt(String.valueOf(charSequence));
                seekBar.setProgress(Math.min(num, 20));
            }

            @Override
            public void afterTextChanged(Editable editable) {
            }
        });
        container1.addView(textView);
        container1.addView(editText);

        TextView longInfo = new TextView(this);
        longInfo.setGravity(Gravity.CENTER);
        longInfo.setText(R.string.addon_keyboard_longpress_info);
        longInfo.setTextSize(15f);

        Button keyboardSet = new Button(this);
        keyboardSet.setText(R.string.addon_keyboard_set);
        keyboardSet.setOnClickListener(view -> {
            startActivity(new Intent(SetActivity.this, ButtonSetActivity.class));
            finish();
        });

        TextView keyboardSetInfo = new TextView(this);
        keyboardSetInfo.setGravity(Gravity.CENTER);
        keyboardSetInfo.setText(R.string.addon_keyboard_set_info);
        keyboardSetInfo.setTextSize(15f);

        keyboardLayout.setVisibility(View.GONE);
        keyboardLayout.setOrientation(LinearLayout.VERTICAL);
        keyboardLayout.addView(keyboardInfo);
        keyboardLayout.addView(useKeyboard);
        keyboardLayout.addView(useKeyboardInfo);
        keyboardLayout.addView(useSpecialPause);
        keyboardLayout.addView(specialPauseInfo);
        keyboardLayout.addView(lockButtonPosition);
        keyboardLayout.addView(lockInfo);
        keyboardLayout.addView(container1);
        keyboardLayout.addView(seekBar);
        keyboardLayout.addView(longInfo);
        keyboardLayout.addView(keyboardSet);
        keyboardLayout.addView(keyboardSetInfo);

        String userdataName = getString(R.string.addon_userdata_name);
        Button userdataExpand = new Button(this);
        LinearLayout userdataLayout = new LinearLayout(this);

        userdataExpand.setText(String.format("▽ %s ▽", userdataName));
        userdataExpand.setTypeface(Typeface.DEFAULT_BOLD);
        userdataExpand.setTextSize(15f);
        userdataExpand.setBackgroundDrawable(oval);
        userdataExpand.setLayoutParams(marginParams);
        userdataExpand.setOnClickListener(view -> {
            boolean isVisible = userdataLayout.getVisibility() == View.VISIBLE;
            ((Button) view).setText(isVisible ? String.format("▽ %s ▽", userdataName) : String.format("△ %s △", userdataName));
            userdataLayout.setVisibility(isVisible ? View.GONE : View.VISIBLE);
        });

        TextView userdataInfo = new TextView(this);
        userdataInfo.setGravity(Gravity.CENTER);
        userdataInfo.setText(R.string.addon_userdata_info);
        userdataInfo.setTextSize(15f);

        final Button buttonImportFromExternal = new Button(this);
        buttonImportFromExternal.setText(R.string.addon_userdata_importfromexternal);
        buttonImportFromExternal.setOnClickListener(view -> Toast.makeText(this, R.string.addon_userdata_importfromexternal_toast1, Toast.LENGTH_SHORT).show());
        buttonImportFromExternal.setOnLongClickListener(view -> {
            try {
                InputStream inputStream = getAssets().open("userdata.zip");
                if (inputStream != null) {
                    File userdata_import = new File(getUserDataFile(this), "userdata");

                    if (!userdata_import.exists()) userdata_import.mkdir();
                    ZipInputStream zipInputStream = new ZipInputStream(inputStream);
                    // 读取ZipEntry对象
                    ZipEntry zipEntry = zipInputStream.getNextEntry();
                    // 遍历ZipEntry对象并解压缩文件
                    byte[] buffer = new byte[1024];
                    while (zipEntry != null) {
                        // 提取zip文件中的唯一一个目录结构下的所有文件
                        if (!zipEntry.isDirectory()) {
                            // 获取文件名并创建新文件。
                            String fileName = new File(zipEntry.getName()).getName();
                            File newFile = new File(userdata_import, fileName);
                            // 写出文件流
                            FileOutputStream fileOutputStream = new FileOutputStream(newFile);
                            int readLength;
                            while ((readLength = zipInputStream.read(buffer)) > 0) {
                                fileOutputStream.write(buffer, 0, readLength);
                            }
                            fileOutputStream.close();
                        }
                        // 关闭当前ZipEntry，并移到下一个ZipEntry。
                        zipInputStream.closeEntry();
                        zipEntry = zipInputStream.getNextEntry();
                    }
                    // 关闭ZipInputStream对象
                    zipInputStream.close();
                    inputStream.close();
                }
                Toast.makeText(SetActivity.this, R.string.addon_userdata_importfromexternal_toast2, Toast.LENGTH_SHORT).show();
            } catch (IOException e) {
                Toast.makeText(SetActivity.this, R.string.addon_userdata_importfromexternal_toast3, Toast.LENGTH_SHORT).show();
                e.printStackTrace();
            }
            return true;
        });

        TextView externalInfo = new TextView(this);
        externalInfo.setGravity(Gravity.CENTER);
        externalInfo.setText(R.string.addon_userdata_importfromexternal_info);
        externalInfo.setTextSize(15f);
        externalInfo.setPadding(0, 0, 0, 30);

        final Button buttonImport = new Button(this);
        buttonImport.setText(R.string.addon_userdata_import);

        buttonImport.setOnClickListener(view -> {
            Toast.makeText(SetActivity.this, R.string.addon_userdata_import_toast1, Toast.LENGTH_SHORT).show();
            //通过系统的文件浏览器选择一个文件
            Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
            //筛选，只显示可以“打开”的结果，如文件(而不是联系人或时区列表)
            intent.addCategory(Intent.CATEGORY_OPENABLE);
            intent.setType("application/zip");
            startActivityForResult(intent, 99);
        });
        final Button buttonImportFromBackup = new Button(this);
        buttonImportFromBackup.setText(R.string.addon_userdata_importfrombackup);
        buttonImportFromBackup.setOnClickListener(view -> {
            PopFragment popFragment = new PopFragment();
            popFragment.show(getFragmentManager(), "pop");
        });

        final Button buttonExport = new Button(this);
        buttonExport.setText(R.string.addon_userdata_export);
        buttonExport.setOnClickListener(view -> {
            Intent intent = new Intent(Intent.ACTION_CREATE_DOCUMENT);
            intent.addCategory(Intent.CATEGORY_OPENABLE);
            // 文件类型
            intent.setType("application/zip");
            // 文件名称
            intent.putExtra(Intent.EXTRA_TITLE, getString(R.string.addon_userdata_export_filename));
            startActivityForResult(intent, 66);
        });
        final CheckBox useExternalPath = new CheckBox(this);
        useExternalPath.setText(R.string.addon_userdata_useExternalPath);
        useExternalPath.setChecked(sharedPreferences.getBoolean("useExternalPath", Build.VERSION.SDK_INT >= Build.VERSION_CODES.M));
        useExternalPath.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("useExternalPath", bool).apply());
        useExternalPath.setLayoutParams(wrapWrapParams);
        useExternalPath.setPadding(0, 30, 0, 30);

        TextView useExternalPathInfo = new TextView(this);
        useExternalPathInfo.setGravity(Gravity.CENTER);
        useExternalPathInfo.setText(R.string.addon_userdata_useExternalPath_info);
        useExternalPathInfo.setTextSize(15f);

        final CheckBox autoBackup = new CheckBox(this);
        autoBackup.setText(R.string.addon_userdata_autobackup);
        autoBackup.setChecked(sharedPreferences.getBoolean("autoBackUp", true));
        autoBackup.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("autoBackUp", bool).apply());
        autoBackup.setLayoutParams(wrapWrapParams);
        autoBackup.setPadding(0, 30, 0, 30);

        TextView autoBackupInfo = new TextView(this);
        autoBackupInfo.setGravity(Gravity.CENTER);
        autoBackupInfo.setText(R.string.addon_userdata_autobackup_info);
        autoBackupInfo.setTextSize(15f);
        userdataLayout.setVisibility(View.GONE);
        userdataLayout.setOrientation(LinearLayout.VERTICAL);

        userdataLayout.addView(userdataInfo);
        userdataLayout.addView(buttonImportFromExternal);
        userdataLayout.addView(externalInfo);
        userdataLayout.addView(buttonImport);
        userdataLayout.addView(buttonImportFromBackup);
        userdataLayout.addView(buttonExport);
        userdataLayout.addView(useExternalPath);
        userdataLayout.addView(useExternalPathInfo);
        userdataLayout.addView(autoBackup);
        userdataLayout.addView(autoBackupInfo);


        String otherName = getString(R.string.addon_other_name);
        Button otherExpand = new Button(this);
        LinearLayout otherLayout = new LinearLayout(this);

        otherExpand.setText(String.format("▽ %s ▽", otherName));
        otherExpand.setTypeface(Typeface.DEFAULT_BOLD);
        otherExpand.setTextSize(15f);
        otherExpand.setBackgroundDrawable(oval);
        otherExpand.setLayoutParams(marginParams);
        otherExpand.setOnClickListener(view -> {
            boolean isVisible = otherLayout.getVisibility() == View.VISIBLE;
            ((Button) view).setText(isVisible ? String.format("▽ %s ▽", otherName) : String.format("△ %s △", otherName));
            otherLayout.setVisibility(isVisible ? View.GONE : View.VISIBLE);
        });

        TextView otherInfo = new TextView(this);
        otherInfo.setGravity(Gravity.CENTER);
        otherInfo.setText(R.string.addon_other_info);
        otherInfo.setTextSize(15f);

        final CheckBox heavyWeapon = new CheckBox(this);
        heavyWeapon.setText(R.string.addon_other_heavyweaponaccl);
        heavyWeapon.setChecked(sharedPreferences.getBoolean("heavyWeaponAccel", false));
        heavyWeapon.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("heavyWeaponAccel", bool).apply());
        heavyWeapon.setLayoutParams(wrapWrapParams);
        heavyWeapon.setPadding(0, 30, 0, 30);

        TextView heavyWeaponInfo = new TextView(this);
        heavyWeaponInfo.setGravity(Gravity.CENTER);
        heavyWeaponInfo.setText(R.string.addon_other_heavyweaponaccl_info);
        heavyWeaponInfo.setTextSize(15f);


        final CheckBox smoothCursor = new CheckBox(this);
        smoothCursor.setText(R.string.addon_other_smooothcursor);
        smoothCursor.setChecked(sharedPreferences.getBoolean("useSmoothCursor", true));
        smoothCursor.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("useSmoothCursor", bool).apply());
        smoothCursor.setLayoutParams(wrapWrapParams);
        smoothCursor.setPadding(0, 30, 0, 30);

        TextView smoothCursorInfo = new TextView(this);
        smoothCursorInfo.setGravity(Gravity.CENTER);
        smoothCursorInfo.setText(R.string.addon_other_smooothcursor_info);
        smoothCursorInfo.setTextSize(15f);


        final CheckBox newShovel = new CheckBox(this);
        newShovel.setText(R.string.addon_other_newshovel);
        newShovel.setChecked(sharedPreferences.getBoolean("useNewShovel", true));
        newShovel.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("useNewShovel", bool).apply());
        newShovel.setLayoutParams(wrapWrapParams);
        newShovel.setPadding(0, 30, 0, 30);

        TextView newShovelInfo = new TextView(this);
        newShovelInfo.setGravity(Gravity.CENTER);
        newShovelInfo.setText(R.string.addon_other_newshovel_info);
        newShovelInfo.setTextSize(15f);


        otherLayout.setVisibility(View.GONE);
        otherLayout.setOrientation(LinearLayout.VERTICAL);
        otherLayout.addView(otherInfo);
        otherLayout.addView(heavyWeapon);
        otherLayout.addView(heavyWeaponInfo);
        otherLayout.addView(smoothCursor);
        otherLayout.addView(smoothCursorInfo);
        otherLayout.addView(newShovel);
        otherLayout.addView(newShovelInfo);

        String secondPlayerName = getString(R.string.addon_secondplayer_name);
        Button secondPlayerExpand = new Button(this);
        LinearLayout secondPlayerLayout = new LinearLayout(this);

        secondPlayerExpand.setText(String.format("▽ %s ▽", secondPlayerName));
        secondPlayerExpand.setTypeface(Typeface.DEFAULT_BOLD);
        secondPlayerExpand.setTextSize(15f);
        secondPlayerExpand.setBackgroundDrawable(oval);
        secondPlayerExpand.setLayoutParams(marginParams);
        secondPlayerExpand.setOnClickListener(view -> {
            boolean isVisible = secondPlayerLayout.getVisibility() == View.VISIBLE;
            ((Button) view).setText(isVisible ? String.format("▽ %s ▽", secondPlayerName) : String.format("△ %s △", secondPlayerName));
            secondPlayerLayout.setVisibility(isVisible ? View.GONE : View.VISIBLE);
        });

        TextView secondPlayerInfo = new TextView(this);
        secondPlayerInfo.setGravity(Gravity.CENTER);
        secondPlayerInfo.setText(R.string.addon_secondplayer_info);
        secondPlayerInfo.setTextSize(15f);


        final Button secondPlayerSet = new Button(this);
        secondPlayerSet.setText(R.string.addon_secondplayer_set);
        secondPlayerSet.setOnClickListener(view -> {
            startActivity(new Intent(SetActivity.this, SecondPlayerSetActivity.class));
            finish();
        });

        TextView secondPlayerSetInfo = new TextView(this);
        secondPlayerSetInfo.setGravity(Gravity.CENTER);
        secondPlayerSetInfo.setText(R.string.addon_secondplayer_set_info);
        secondPlayerSetInfo.setTextSize(15f);


        final Button secondPlayerLaunch = new Button(this);
        secondPlayerLaunch.setText(R.string.addon_secondplayer_launch);
        secondPlayerLaunch.setOnClickListener(view -> {
            startActivity(new Intent(SetActivity.this, SecondPlayerActivity.class));
            finish();
        });

        TextView secondPlayerLaunchInfo = new TextView(this);
        secondPlayerLaunchInfo.setGravity(Gravity.CENTER);
        secondPlayerLaunchInfo.setText(R.string.addon_secondplayer_launch_info);
        secondPlayerLaunchInfo.setTextSize(15f);

        secondPlayerLayout.setVisibility(View.GONE);
        secondPlayerLayout.setOrientation(LinearLayout.VERTICAL);
        secondPlayerLayout.addView(secondPlayerInfo);
        secondPlayerLayout.addView(secondPlayerSet);
        secondPlayerLayout.addView(secondPlayerSetInfo);
        secondPlayerLayout.addView(secondPlayerLaunch);
        secondPlayerLayout.addView(secondPlayerLaunchInfo);

        String inGameName = getString(R.string.addon_ingame_name);
        Button inGameExpand = new Button(this);
        LinearLayout inGameLayout = new LinearLayout(this);

        inGameExpand.setText(String.format("▽ %s ▽", inGameName));
        inGameExpand.setTypeface(Typeface.DEFAULT_BOLD);
        inGameExpand.setTextSize(15f);
        inGameExpand.setBackgroundDrawable(oval);
        inGameExpand.setLayoutParams(marginParams);
        inGameExpand.setOnClickListener(view -> {
            boolean isVisible = inGameLayout.getVisibility() == View.VISIBLE;
            ((Button) view).setText(isVisible ? String.format("▽ %s ▽", inGameName) : String.format("△ %s △", inGameName));
            inGameLayout.setVisibility(isVisible ? View.GONE : View.VISIBLE);
        });

        TextView inGameInfo = new TextView(this);
        inGameInfo.setGravity(Gravity.CENTER);
        inGameInfo.setText(R.string.addon_ingame_info);
        inGameInfo.setTextSize(15f);

        LinearLayout container = new LinearLayout(this);
        container.setOrientation(LinearLayout.VERTICAL);
        container.setLayoutParams(wrapWrapParams);
        final CheckBox manualCollect = new CheckBox(this);
        manualCollect.setText(R.string.addon_ingame_manualcollect);
        manualCollect.setChecked(sharedPreferences.getBoolean("enableManualCollect", false));
        manualCollect.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("enableManualCollect", bool).apply());
        manualCollect.setLayoutParams(matchWrapParams);

        final CheckBox canShop = new CheckBox(this);
        canShop.setText(R.string.addon_ingame_canshop);
        canShop.setChecked(sharedPreferences.getBoolean("disableShop", false));
        canShop.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("disableShop", bool).apply());
        canShop.setLayoutParams(matchWrapParams);

        final CheckBox newOptions = new CheckBox(this);
        newOptions.setText(R.string.addon_ingame_newoptions);
        newOptions.setChecked(sharedPreferences.getBoolean("enableNewOptionsDialog", false));
        newOptions.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("enableNewOptionsDialog", bool).apply());
        newOptions.setLayoutParams(matchWrapParams);


        final CheckBox showCoolDown = new CheckBox(this);
        showCoolDown.setText(R.string.addon_ingame_showcooldown);
        showCoolDown.setChecked(sharedPreferences.getBoolean("showCoolDown", false));
        showCoolDown.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("showCoolDown", bool).apply());
        showCoolDown.setLayoutParams(matchWrapParams);

        container.addView(manualCollect);
        container.addView(canShop);
        container.addView(newOptions);
        container.addView(showCoolDown);
        try {
            Class.forName("com.android.support.CkHomuraMenu");
            final CheckBox useMenu = new CheckBox(this);
            useMenu.setText(R.string.addon_ingame_usemenu);
            useMenu.setChecked(sharedPreferences.getBoolean("useMenu", true));
            useMenu.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("useMenu", bool).apply());
            useMenu.setLayoutParams(matchWrapParams);
            container.addView(useMenu);
        } catch (ClassNotFoundException ignored) {
        }


        TextView newOptionsInfo = new TextView(this);
        newOptionsInfo.setGravity(Gravity.CENTER);
        newOptionsInfo.setText(R.string.addon_ingame_newoptions_info);
        newOptionsInfo.setTextSize(15f);

        TextView showCoolDownInfo = new TextView(this);
        showCoolDownInfo.setGravity(Gravity.CENTER);
        showCoolDownInfo.setText(R.string.addon_ingame_showcooldown_info);
        showCoolDownInfo.setTextSize(15f);

        inGameLayout.setVisibility(View.GONE);
        inGameLayout.setOrientation(LinearLayout.VERTICAL);
        inGameLayout.addView(inGameInfo);
        inGameLayout.addView(container);
        inGameLayout.addView(newOptionsInfo);
        inGameLayout.addView(showCoolDownInfo);

        String appearanceName = getString(R.string.addon_appearance_name);
        Button appearanceExpand = new Button(this);
        LinearLayout appearanceLayout = new LinearLayout(this);

        appearanceExpand.setText(String.format("▽ %s ▽", appearanceName));
        appearanceExpand.setTypeface(Typeface.DEFAULT_BOLD);
        appearanceExpand.setTextSize(15f);
        appearanceExpand.setBackgroundDrawable(oval);
        appearanceExpand.setLayoutParams(marginParams);
        appearanceExpand.setOnClickListener(view -> {
            boolean isVisible = appearanceLayout.getVisibility() == View.VISIBLE;
            ((Button) view).setText(isVisible ? String.format("▽ %s ▽", appearanceName) : String.format("△ %s △", appearanceName));
            appearanceLayout.setVisibility(isVisible ? View.GONE : View.VISIBLE);
        });

        final CheckBox hideCoverLayer = new CheckBox(this);
        hideCoverLayer.setText(R.string.addon_appearance_hidecoverlayer);
        hideCoverLayer.setChecked(sharedPreferences.getBoolean("hideCoverLayer", false));
        hideCoverLayer.setOnCheckedChangeListener((compoundButton, bool) -> sharedPreferences.edit().putBoolean("hideCoverLayer", bool).apply());
        hideCoverLayer.setPadding(0, 20, 0, 20);
        hideCoverLayer.setLayoutParams(wrapWrapParams);


        final CheckBox showHouse = new CheckBox(this);
        final HorizontalScrollView houseChooserContainer = new HorizontalScrollView(this);

        showHouse.setText(R.string.addon_appearance_showhouse);
        showHouse.setChecked(sharedPreferences.getBoolean("showHouse", true));
        showHouse.setOnCheckedChangeListener((compoundButton, bool) -> {
            sharedPreferences.edit().putBoolean("showHouse", bool).apply();
            unzipHoodFromAssetsFiles(sharedPreferences);
            houseChooserContainer.setVisibility(bool ? View.VISIBLE : View.GONE);
        });
        showHouse.setPadding(0, 20, 0, 20);
        showHouse.setLayoutParams(wrapWrapParams);


        houseChooserContainer.setHorizontalScrollBarEnabled(true);
        houseChooserContainer.setVisibility(showHouse.isChecked() ? View.VISIBLE : View.GONE);
        final LinearLayout hoodChooser = new LinearLayout(this);
        for (int i = 0; i < 12; i++) {
            String hoodName = getHoodNameById(i);
            FrameLayout hoodPreview = new FrameLayout(this);
            ImageView hoodImage = new ImageView(this);
            try {
                InputStream inputStream = getAssets().open("Hood2-Preview/" + hoodName + ".png");
                Drawable drawable = Drawable.createFromStream(inputStream, null);
                hoodImage.setImageDrawable(drawable);
                // 在此处将 drawable 设置给你的 ImageView 或其他视图
            } catch (IOException e) {
                e.printStackTrace();
            }
            TextView hoodNameText = new TextView(this);
            hoodNameText.setText(hoodName);
            hoodNameText.setTextColor(isNight ? Color.LTGRAY : Color.DKGRAY);
            hoodNameText.setTextSize(14f);
            FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT, FrameLayout.LayoutParams.WRAP_CONTENT);
            layoutParams.gravity = Gravity.CENTER | Gravity.TOP;
            hoodNameText.setLayoutParams(layoutParams);
            hoodPreview.addView(hoodImage);
            hoodPreview.addView(hoodNameText);
            int houseId = i;
            hoodPreview.setOnClickListener(view -> {
                sharedPreferences.edit().putInt("houseId", houseId).apply();
                unzipHoodFromAssetsFiles(sharedPreferences);
                Toast.makeText(SetActivity.this, getString(R.string.addon_appearance_housechooser_toast) + hoodName, Toast.LENGTH_SHORT).show();
            });
            hoodChooser.addView(hoodPreview);
        }
        houseChooserContainer.addView(hoodChooser);

        appearanceLayout.setVisibility(View.GONE);
        appearanceLayout.setOrientation(LinearLayout.VERTICAL);
        appearanceLayout.addView(hideCoverLayer);
        appearanceLayout.addView(showHouse);
        appearanceLayout.addView(houseChooserContainer);


        String adventureName = getString(R.string.addon_adventure_name);
        Button adventureExpand = new Button(this);
        LinearLayout adventureLayout = new LinearLayout(this);

        adventureExpand.setText(String.format("▽ %s ▽", adventureName));
        adventureExpand.setTypeface(Typeface.DEFAULT_BOLD);
        adventureExpand.setTextSize(15f);
        adventureExpand.setBackgroundDrawable(oval);
        adventureExpand.setLayoutParams(marginParams);
        adventureExpand.setOnClickListener(view -> {
            boolean isVisible = adventureLayout.getVisibility() == View.VISIBLE;
            ((Button) view).setText(isVisible ? String.format("▽ %s ▽", adventureName) : String.format("△ %s △", adventureName));
            adventureLayout.setVisibility(isVisible ? View.GONE : View.VISIBLE);
        });

        TextView hardAdventureInfo = new TextView(this);
        hardAdventureInfo.setGravity(Gravity.CENTER);
        hardAdventureInfo.setText(R.string.addon_adventure_info);
        hardAdventureInfo.setTextSize(15f);


        CheckBox normalLevel = new CheckBox(this);
        normalLevel.setText(R.string.addon_adventure_normallevel);
        normalLevel.setTextSize(16f);
        normalLevel.setPadding(0, 30, 0, 30);
        normalLevel.setChecked(sharedPreferences.getBoolean("normalLevel", true));
        normalLevel.setLayoutParams(wrapWrapParams);

        String normalLevelText1 = getString(R.string.addon_adventure_nornallevel_text1);
        String normalLevelText2 = getString(R.string.addon_adventure_nornallevel_text2);
        TextView normalLevelInfo = new TextView(this);
        normalLevelInfo.setGravity(Gravity.CENTER);
        normalLevelInfo.setText(normalLevel.isChecked() ? normalLevelText1 : normalLevelText2);
        normalLevelInfo.setTextSize(15f);


        Button adventurePicker = new Button(this);
        adventurePicker.setEnabled(!normalLevel.isChecked());
        adventurePicker.setText(String.format("%s→", getString(R.string.addon_adventure_selectadventure)));
        adventurePicker.setOnClickListener(view1 -> {
//            final LinearLayout adventureLayout = new LinearLayout(this);
//            adventureLayout.setOrientation(LinearLayout.VERTICAL);
//            final int selectedId = sharedPreferences.getInt("adventureId", 0);
//
//            AlertDialog dialog = new AlertDialog.Builder(this)
//                    .setTitle(adventureTitle+"↓")
//                    .setView(adventureLayout)
//                    .create();
//
//
//            for (int i = 0; i < adventureNames.length; i++) {
//                Button tv = new Button(this);
//                tv.setText(adventureNames[i]);
//                int adventureId = i;
//                if (adventureId == selectedId) {
//                    tv.append("✓");
//                    tv.setTextColor(isNight?Color.GREEN:Color.YELLOW);
//                }
//                tv.setOnClickListener(view -> {
//                    sharedPreferences.edit().putInt("adventureId", adventureId).apply();
//                    File destDir = new File(getUserDataFile(this), "properties");
//                    if (!destDir.exists()) {
//                        destDir.mkdirs();
//                    }
//                    try {
//                        InputStream is = getAssets().open("levels/" + adventureFiles[adventureId]);
//                        FileOutputStream fos = new FileOutputStream(new File(destDir, "levels.xml"));
//                        byte[] buffer = new byte[1024];
//                        int byteCount;
//                        while ((byteCount = is.read(buffer)) != -1) {// 循环从输入流读取
//                            // buffer字节
//                            fos.write(buffer, 0, byteCount);// 将读取的输入流写入到输出流
//                        }
//                        fos.flush();// 刷新缓冲区
//                        is.close();
//                        fos.close();
//                        Toast.makeText(this, getString(R.string.addon_ingame_importlevels_toast4)+adventureNames[adventureId], Toast.LENGTH_SHORT).show();
//                    } catch (IOException e) {
//                        throw new RuntimeException(e);
//                    }
//                    dialog.dismiss();
//                });
//                adventureLayout.addView(tv);
//            }
//            Button tv = new Button(this);
//            tv.setText(R.string.addon_ingame_importlevels);
//            if (selectedId == -1){
//                tv.append("✓");
//                tv.setTextColor(Color.GREEN);
//            }
//            tv.setOnClickListener(view -> {
//                Toast.makeText(SetActivity.this, R.string.addon_ingame_importlevels_toast1, Toast.LENGTH_SHORT).show();
//                //通过系统的文件浏览器选择一个文件
//                Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
//                //筛选，只显示可以“打开”的结果，如文件(而不是联系人或时区列表)
//                intent.addCategory(Intent.CATEGORY_OPENABLE);
//                intent.setType("text/xml");
//                startActivityForResult(intent, 33);
//                dialog.dismiss();
//            });
//            adventureLayout.addView(tv);
//            dialog.show();
            AdventureChooseFragment fragment = new AdventureChooseFragment();
            fragment.show(getFragmentManager(), "tag1");
        });
        adventurePicker.setLayoutParams(matchWrapParams);
        adventurePicker.setPadding(0, 30, 0, 30);


        String hardAdventureSelectInfoText1 = getString(R.string.addon_adventure_selectadventure_info_text1);
        String hardAdventureSelectInfoText2 = getString(R.string.addon_adventure_selectadventure_info_text2);
        TextView hardAdventureSelectInfo = new TextView(this);
        hardAdventureSelectInfo.setPadding(20,0,20,0);
        hardAdventureSelectInfo.setGravity(Gravity.CENTER);
        hardAdventureSelectInfo.setText(normalLevel.isChecked() ? hardAdventureSelectInfoText1 : hardAdventureSelectInfoText2);
        hardAdventureSelectInfo.setTextSize(15f);

        normalLevel.setOnCheckedChangeListener((compoundButton, b) -> {
            adventurePicker.setEnabled(!b);
            normalLevelInfo.setText(b ? normalLevelText1 : normalLevelText2);
            hardAdventureSelectInfo.setText(b ? hardAdventureSelectInfoText1 : hardAdventureSelectInfoText2);
            sharedPreferences.edit().putBoolean("normalLevel",b).apply();
        });

        adventureLayout.setVisibility(View.GONE);
        adventureLayout.setOrientation(LinearLayout.VERTICAL);
        adventureLayout.addView(hardAdventureInfo);
        adventureLayout.addView(normalLevel);
        adventureLayout.addView(normalLevelInfo);
        adventureLayout.addView(adventurePicker);
        adventureLayout.addView(hardAdventureSelectInfo);


        final Button buttonAbout = new Button(this);
        buttonAbout.setText(R.string.addon_contact_me);
        buttonAbout.setTextSize(15f);
        buttonAbout.setTypeface(Typeface.DEFAULT_BOLD);
        buttonAbout.setOnClickListener(view -> new AlertDialog.Builder(this)
                .setTitle(R.string.addon_contact_me_title)
                .setMessage(R.string.addon_contact_me_message)
                .setPositiveButton(R.string.addon_contact_me_button, (dialogInterface, i1) -> {
                    String url = "https://space.bilibili.com/480240783";
                    Intent intent = new Intent(Intent.ACTION_VIEW);
                    intent.setData(Uri.parse(url));
                    startActivity(intent);
                })
                .show());

        final Button buttonOpenGame = new Button(this);
        buttonOpenGame.setText(R.string.addon_launch);
        buttonOpenGame.setTextSize(15f);
        buttonOpenGame.setTypeface(Typeface.DEFAULT_BOLD);
        buttonOpenGame.setOnClickListener(view -> {
            startActivity(new Intent(SetActivity.this, EnhanceActivity.class));
            finish();
        });

        final Button buttonHide = new Button(this);
        PackageManager packageManager = getPackageManager();
        ComponentName set = new ComponentName(getPackageName(), SetActivityEntrance.class.getName());
        buttonHide.setText(String.format(getString(R.string.addon_hide_self), packageManager.getComponentEnabledSetting(set) == PackageManager.COMPONENT_ENABLED_STATE_DISABLED ? "显示" : "隐藏"));
        buttonHide.setTextSize(15f);
        buttonHide.setTypeface(Typeface.DEFAULT_BOLD);
        buttonHide.setOnClickListener(view -> hideOrNot());

        linearLayout.addView(aspectExpand);
        linearLayout.addView(aspectLayout);

        linearLayout.addView(keyboardExpand);
        linearLayout.addView(keyboardLayout);

        linearLayout.addView(userdataExpand);
        linearLayout.addView(userdataLayout);

        linearLayout.addView(otherExpand);
        linearLayout.addView(otherLayout);

        linearLayout.addView(secondPlayerExpand);
        linearLayout.addView(secondPlayerLayout);

        linearLayout.addView(inGameExpand);
        linearLayout.addView(inGameLayout);

        linearLayout.addView(appearanceExpand);
        linearLayout.addView(appearanceLayout);

        linearLayout.addView(adventureExpand);
        linearLayout.addView(adventureLayout);

        linearLayout.addView(buttonAbout);
        linearLayout.addView(buttonOpenGame);
        linearLayout.addView(buttonHide);
        scrollView.addView(linearLayout);
        setContentView(scrollView);


    }

    private String getHoodNameById(int i) {
        switch (i) {
            case 0:
                return "House1";
            case 1:
                return "House2";
            case 2:
                return "Gold1";
            case 3:
                return "Gold2";
            case 4:
                return "Hounted1";
            case 5:
                return "Hounted2";
            case 6:
                return "Clown1";
            case 7:
                return "Clown2";
            case 8:
                return "Future1";
            case 9:
                return "Future2";
            case 10:
                return "Caravan1";
            case 11:
                return "Caravan2";
            default:
                return "";
        }
    }

    public void unzipHoodFromAssetsFiles(SharedPreferences sharedPreferences) {
        boolean bool = sharedPreferences.getBoolean("showHouse", true);
        File destDir = new File(getUserDataFile(this), "reanim/mainmenu3");
        if (!destDir.exists()) {
            destDir.mkdirs();
        }
        for (int i = 1; i < 5; i++) {
            File destFile = new File(destDir, "Hood" + i + ".png");
            if (i == 2) {
                try {
                    String assetsFile = bool ? "Hood2-" + getHoodNameById(sharedPreferences.getInt("houseId", 0)) + ".png" : "Hood2-orig.png";
                    InputStream is = getAssets().open("Hood2/" + assetsFile);
                    FileOutputStream fos = new FileOutputStream(destFile);
                    byte[] buffer = new byte[1024];
                    int byteCount;
                    while ((byteCount = is.read(buffer)) != -1) {// 循环从输入流读取
                        // buffer字节
                        fos.write(buffer, 0, byteCount);// 将读取的输入流写入到输出流
                    }
                    fos.flush();// 刷新缓冲区
                    is.close();
                    fos.close();
                } catch (Exception e) {
                    //  throw new RuntimeException(e);
                }
                continue;
            }
            try {
                InputStream is = getAssets().open(bool ? "Hood" + i + "-house.png" : "Hood" + i + "-orig.png");
                FileOutputStream fos = new FileOutputStream(destFile);
                byte[] buffer = new byte[1024];
                int byteCount;
                while ((byteCount = is.read(buffer)) != -1) {// 循环从输入流读取
                    // buffer字节
                    fos.write(buffer, 0, byteCount);// 将读取的输入流写入到输出流
                }
                fos.flush();// 刷新缓冲区
                is.close();
                fos.close();
            } catch (Exception e) {
                //  throw new RuntimeException(e);
            }
        }
        File destFile = new File(destDir, "house_hill.png");
        try {
            InputStream is = getAssets().open(bool ? "house_hill-house.png" : "house_hill-orig.png");
            FileOutputStream fos = new FileOutputStream(destFile);
            byte[] buffer = new byte[1024];
            int byteCount;
            while ((byteCount = is.read(buffer)) != -1) {// 循环从输入流读取
                // buffer字节
                fos.write(buffer, 0, byteCount);// 将读取的输入流写入到输出流
            }
            fos.flush();// 刷新缓冲区
            is.close();
            fos.close();
        } catch (Exception e) {
            //    throw new RuntimeException(e);
        }
    }

    public static class PopFragment extends DialogFragment {

        @Override
        public void onActivityCreated(Bundle savedInstanceState) {

            Window window = getDialog().getWindow();
            window.setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
            super.onActivityCreated(savedInstanceState);
        }

        @Override
        public void onStart() {
            Window window = getDialog().getWindow();
            window.setLayout(getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE ? getResources().getDisplayMetrics().heightPixels : getResources().getDisplayMetrics().widthPixels - 150, -2);
            super.onStart();
        }

        @Override
        public Dialog onCreateDialog(Bundle savedInstanceState) {
            Dialog dialog = new Dialog(getActivity());
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP)
                dialog.requestWindowFeature(Window.FEATURE_CONTENT_TRANSITIONS);
            dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
            dialog.setCanceledOnTouchOutside(true);
            return dialog;
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
            List<Pair<String, Long>> backupsList = findNumDirs(getUserDataFile(getActivity()));
            ListView listView = new ListView(getActivity());
            if (backupsList.isEmpty()) {
                Toast.makeText(getActivity(), R.string.addon_auto_backup_toast1, Toast.LENGTH_SHORT).show();
                new Handler().postDelayed(this::dismiss, 1000);
                return listView;
            }
            boolean isNight = (getResources().getConfiguration().uiMode & Configuration.UI_MODE_NIGHT_YES) == Configuration.UI_MODE_NIGHT_YES;
            float density = getResources().getDisplayMetrics().density;
            ShapeDrawable oval = new ShapeDrawable(new RoundRectShape(new float[]{20 * density, 20 * density, 20 * density, 20 * density, 20 * density, 20 * density, 20 * density, 20 * density}, null, null));
            oval.getPaint().setColor(isNight ? 0xff424c50 : Color.LTGRAY);
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN)
                listView.setBackground(oval);


            listView.setAdapter(new BaseAdapter() {
                @Override
                public int getCount() {
                    return backupsList.size();
                }

                @Override
                public Object getItem(int i) {
                    return backupsList.get(i);
                }

                @Override
                public long getItemId(int i) {
                    return i;
                }

                @Override
                public View getView(int i, View view, ViewGroup viewGroup) {
                    view = new TextView(getActivity());
                    ((TextView) view).setText(backupsList.get(i).first);
                    ((TextView) view).setGravity(Gravity.CENTER);
                    ((TextView) view).setHeight((int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 40, getActivity().getResources().getDisplayMetrics()));
                    ((TextView) view).setTextSize(16f);
                    ((TextView) view).setTextColor(isNight ? Color.WHITE : Color.BLACK);
                    view.setOnClickListener(view1 -> Toast.makeText(getActivity(), R.string.addon_auto_backup_toast2, Toast.LENGTH_SHORT).show());
                    view.setOnLongClickListener(view12 -> {
                        String backupFile = backupsList.get(i).first;
                        File file = new File(getUserDataFile(getActivity()), backupFile);
                        File destFile = new File(getUserDataFile(getActivity()), "userdata");
                        deleteRecursive(destFile);
                        try {
                            copyDir(file, destFile);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        Toast.makeText(getActivity(), R.string.addon_auto_backup_toast3, Toast.LENGTH_SHORT).show();
                        return true;
                    });
                    return view;
                }
            });
            listView.setLayoutTransition(new LayoutTransition());
            listView.setOnItemClickListener((parent, view, position, id) -> dismiss());
            return listView;
        }
    }

    public static class AdventureChooseFragment extends DialogFragment {

        @Override
        public void onActivityCreated(Bundle savedInstanceState) {
            Window window = getDialog().getWindow();
            window.setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
            super.onActivityCreated(savedInstanceState);
        }

        @Override
        public void onStart() {
            Window window = getDialog().getWindow();
            window.setLayout(getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE ? getResources().getDisplayMetrics().heightPixels : getResources().getDisplayMetrics().widthPixels - 150, -2);
            super.onStart();
        }

        @Override
        public Dialog onCreateDialog(Bundle savedInstanceState) {
            Dialog dialog = new Dialog(getActivity());
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP)
                dialog.requestWindowFeature(Window.FEATURE_CONTENT_TRANSITIONS);
            dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
            dialog.setCanceledOnTouchOutside(true);
            return dialog;
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
            final String[] adventureFiles = new String[]{"levels-normal.xml", "levels-middle.xml", "levels-hard.xml"};
            final String[] adventureNames = new String[]{getActivity().getString(R.string.addon_adventure_adventurename1), getActivity().getString(R.string.addon_adventure_adventurename2), getActivity().getString(R.string.addon_adventure_adventurename3)};
            final LinearLayout adventureLayout = new LinearLayout(getActivity());
            adventureLayout.setOrientation(LinearLayout.VERTICAL);
            SharedPreferences sharedPreferences = getActivity().getSharedPreferences("data", 0);
            final int selectedId = sharedPreferences.getInt("adventureId", 0);
            boolean isNight = (getResources().getConfiguration().uiMode & Configuration.UI_MODE_NIGHT_YES) == Configuration.UI_MODE_NIGHT_YES;

            for (int i = 0; i < adventureNames.length; i++) {
                Button tv = new Button(getActivity());
                tv.setText(adventureNames[i]);
                int adventureId = i;
                if (adventureId == selectedId) {
                    tv.append("✓");
                    tv.setTextColor(isNight ? Color.GREEN : Color.YELLOW);
                }
                tv.setOnClickListener(view -> {
                    sharedPreferences.edit().putInt("adventureId", adventureId).apply();
                    File destDir = new File(getUserDataFile(getActivity()), "properties");
                    if (!destDir.exists()) {
                        destDir.mkdirs();
                    }
                    try {
                        InputStream is = getActivity().getAssets().open("levels/" + adventureFiles[adventureId]);
                        FileOutputStream fos = new FileOutputStream(new File(destDir, "levels.xml"));
                        byte[] buffer = new byte[1024];
                        int byteCount;
                        while ((byteCount = is.read(buffer)) != -1) {// 循环从输入流读取
                            // buffer字节
                            fos.write(buffer, 0, byteCount);// 将读取的输入流写入到输出流
                        }
                        fos.flush();// 刷新缓冲区
                        is.close();
                        fos.close();
                        Toast.makeText(getActivity(), getActivity().getString(R.string.addon_adventure_importlevels_toast4) + adventureNames[adventureId], Toast.LENGTH_SHORT).show();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                    dismiss();
                });
                adventureLayout.addView(tv);
            }
            Button tv = new Button(getActivity());
            tv.setText(getActivity().getString(R.string.addon_adventure_importlevels));
            if (selectedId == -1) {
                tv.append("✓");
                tv.setTextColor(Color.GREEN);
            }
            tv.setOnClickListener(view -> {
                Toast.makeText(getActivity(), getActivity().getString(R.string.addon_adventure_importlevels_toast1), Toast.LENGTH_SHORT).show();
                //通过系统的文件浏览器选择一个文件
                Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
                //筛选，只显示可以“打开”的结果，如文件(而不是联系人或时区列表)
                intent.addCategory(Intent.CATEGORY_OPENABLE);
                intent.setType("text/xml");
                getActivity().startActivityForResult(intent, 33);
                dismiss();
            });
            adventureLayout.addView(tv);
            return adventureLayout;
        }
    }

    public static void copyDir(File srcDir, File destDir) throws IOException {
        if (srcDir.isDirectory()) {
            if (!destDir.exists()) {
                destDir.mkdirs();
            }

            String[] children = srcDir.list();
            if (children == null) return;
            for (String child : children) {
                File srcFile = new File(srcDir, child);
                File destFile = new File(destDir, child);
                copyDir(srcFile, destFile);
            }
        } else {
            FileInputStream inputStream = new FileInputStream(srcDir);
            FileOutputStream outputStream = new FileOutputStream(destDir);

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) > 0) {
                outputStream.write(buffer, 0, bytesRead);
            }

            inputStream.close();
            outputStream.close();
        }
    }

    public static void deleteRecursive(File file) {
        if (file.isFile()) {
            file.delete();
        } else {
            // 如果是文件夹，递归删除
            File[] files = file.listFiles();
            if (files != null && files.length > 0) {
                for (File subFile : files) {
                    deleteRecursive(subFile);
                }
            }
            file.delete();
        }
    }

    public static List<Pair<String, Long>> findNumDirs(File dir) {
        List<Pair<String, Long>> list = new ArrayList<>();
        if (dir.exists() && dir.isDirectory()) {
            File[] files = dir.listFiles((dir1, name) -> {
                // 判断只要是数字开头的文件夹就符合要求
                return new File(dir1, name).isDirectory() && Character.isDigit(name.charAt(0));
            });
            if (files != null && files.length > 0) {
                // 将文件夹的名称和修改时间存入Pair中，再将Pair存入list中
                for (File file : files) {
                    String dirName = file.getName();
                    long modifiedTime = file.lastModified();
                    Pair<String, Long> pair = new Pair<>(dirName, modifiedTime);
                    list.add(pair);
                }
                // 按照修改时间排序
                Collections.sort(list, (o1, o2) -> o2.second.compareTo(o1.second));
            }
        }
        return list;
    }


    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == 33 && resultCode == Activity.RESULT_OK) {
            Uri uri = data.getData();
            if (uri != null) {
                try {
                    InputStream inputStream = getContentResolver().openInputStream(uri);
                    if (inputStream != null) {
                        File destDir = new File(getUserDataFile(this), "properties");
                        if (!destDir.exists()) {
                            destDir.mkdirs();
                        }
                        FileOutputStream fos = new FileOutputStream(new File(destDir, "levels.xml"));
                        byte[] buffer = new byte[1024];
                        int byteCount;
                        while ((byteCount = inputStream.read(buffer)) != -1) {// 循环从输入流读取
                            // buffer字节
                            fos.write(buffer, 0, byteCount);// 将读取的输入流写入到输出流
                        }
                        fos.flush();// 刷新缓冲区
                        inputStream.close();
                        fos.close();
                    }
                    getSharedPreferences("data", 0).edit().putInt("adventureId", -1).apply();
                    Toast.makeText(this, R.string.addon_adventure_importlevels_toast2, Toast.LENGTH_SHORT).show();
                } catch (IOException e) {
                    Toast.makeText(this, R.string.addon_adventure_importlevels_toast3, Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                }

            }
        }

        if (requestCode == 66 && resultCode == Activity.RESULT_OK) {
            Uri uri = data.getData();
            if (uri != null) {
                try {
                    OutputStream outputStream = getContentResolver().openOutputStream(uri);
                    if (outputStream != null) {
                        File userdata = new File(getUserDataFile(this), "userdata");
                        ZipOutputStream zipOutputStream = new ZipOutputStream(outputStream);
                        addFolderToZip(userdata, zipOutputStream);
                        zipOutputStream.close();
                        outputStream.close();
                    }
                    Toast.makeText(this, R.string.addon_export_toast1, Toast.LENGTH_SHORT).show();
                } catch (IOException e) {
                    Toast.makeText(this, R.string.addon_export_toast2, Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                }

            }
        }

        if (requestCode == 99 && resultCode == Activity.RESULT_OK) {
            Uri uri = data.getData();
            if (uri != null) {
                try {
                    InputStream inputStream = getContentResolver().openInputStream(uri);
                    if (inputStream != null) {
                        File userdata_import = new File(getUserDataFile(this), "userdata");
                        deleteRecursive(userdata_import);
                        if (!userdata_import.exists()) userdata_import.mkdir();
                        ZipInputStream zipInputStream = new ZipInputStream(inputStream);
                        // 读取ZipEntry对象
                        ZipEntry zipEntry = zipInputStream.getNextEntry();
                        // 遍历ZipEntry对象并解压缩文件
                        byte[] buffer = new byte[1024];
                        while (zipEntry != null) {
                            // 提取zip文件中的唯一一个目录结构下的所有文件
                            if (!zipEntry.isDirectory()) {
                                // 获取文件名并创建新文件。
                                String fileName = new File(zipEntry.getName()).getName();
                                File newFile = new File(userdata_import, fileName);
                                // 写出文件流
                                FileOutputStream fileOutputStream = new FileOutputStream(newFile);
                                int readLength;
                                while ((readLength = zipInputStream.read(buffer)) > 0) {
                                    fileOutputStream.write(buffer, 0, readLength);
                                }
                                fileOutputStream.close();
                            }
                            // 关闭当前ZipEntry，并移到下一个ZipEntry。
                            zipInputStream.closeEntry();
                            zipEntry = zipInputStream.getNextEntry();
                        }
                        // 关闭ZipInputStream对象
                        zipInputStream.close();
                        inputStream.close();
                    }
                    Toast.makeText(this, R.string.addon_import_toast1, Toast.LENGTH_SHORT).show();
                } catch (IOException e) {
                    Toast.makeText(this, R.string.addon_import_toast2, Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                }

            }
        }
    }


    public static void addFolderToZip(File folder, ZipOutputStream zipOutputStream) throws IOException {
        File[] files = folder.listFiles();
        if (files == null) return;
        for (File file : files) {
            if (file.isDirectory()) {
                addFolderToZip(file, zipOutputStream);
            } else {
                byte[] buffer = new byte[1024];
                FileInputStream fileInputStream = new FileInputStream(file);
                zipOutputStream.putNextEntry(new ZipEntry(file.getName()));
                int length;
                while ((length = fileInputStream.read(buffer)) > 0) {
                    zipOutputStream.write(buffer, 0, length);
                }
                fileInputStream.close();
            }
        }
    }


    @Override
    public void onBackPressed() {
        finish();
        super.onBackPressed();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuItem item1 = menu.add(0, 1, 1, R.string.addon_hide_self_itemname);
        item1.setCheckable(true);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        menu.findItem(1).setChecked(getPackageManager().getComponentEnabledSetting(new ComponentName(getPackageName(), SetActivityEntrance.class.getName())) == PackageManager.COMPONENT_ENABLED_STATE_DISABLED);
        return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onMenuItemSelected(int i, MenuItem menuItem) {
        hideOrNot();
        return super.onMenuItemSelected(i, menuItem);
    }

    public void hideOrNot() {

        PackageManager packageManager = getPackageManager();
        ComponentName set = new ComponentName(getPackageName(), SetActivityEntrance.class.getName());
        if (packageManager.getComponentEnabledSetting(set) == PackageManager.COMPONENT_ENABLED_STATE_DISABLED) {
            new AlertDialog.Builder(this)
                    .setTitle(R.string.addon_hide_self_title1)
                    .setMessage(R.string.addon_hide_self_message1)
                    .setNegativeButton(R.string.addon_hide_self_back, null)
                    .setPositiveButton(R.string.addon_hide_self_ok, (dialogInterface, i1) -> packageManager.setComponentEnabledSetting(set, PackageManager.COMPONENT_ENABLED_STATE_ENABLED, 0))
                    .show();
        } else {
            new AlertDialog.Builder(this)
                    .setTitle(R.string.addon_hide_self_title2)
                    .setMessage(R.string.addon_hide_self_message2)
                    .setNegativeButton(R.string.addon_hide_self_back, null)
                    .setPositiveButton(R.string.addon_hide_self_ok, (dialogInterface, i1) -> packageManager.setComponentEnabledSetting(set, PackageManager.COMPONENT_ENABLED_STATE_DISABLED, 0))
                    .show();
        }
    }

}