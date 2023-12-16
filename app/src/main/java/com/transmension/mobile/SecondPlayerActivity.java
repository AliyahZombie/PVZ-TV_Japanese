package com.transmension.mobile;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.FileObserver;
import android.view.KeyEvent;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Locale;

public class SecondPlayerActivity extends MainActivity {
    //fileObserver用于观测存放文件夹变动，并在存档更新时保留一份备份
    private boolean isFileObserverLaunched = false;
    private FileObserver fileObserver;

    //用于fileObserver备份存档的一些函数
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

    public void checkAndDeleteOldBackups() {
        File file = getExternalFilesDir(null);
        if (file.exists() && file.isDirectory()) {

            File[] files = file.listFiles((dir1, name) -> {
                // 判断只要是数字开头的文件夹就符合要求
                return new File(dir1, name).isDirectory() && Character.isDigit(name.charAt(0));
            });
            if (files != null && files.length > 0) {
                // 对文件夹按照修改时间进行排序
                Arrays.sort(files, (f1, f2) -> Long.compare(f2.lastModified(), f1.lastModified()));
                // 如果文件夹数量超过20个，进行删除操作
                if (files.length > 20) {
                    // 遍历排序后的文件夹列表，删除20个之后的文件夹
                    for (int i = 20; i < files.length; i++) {
                        File oldFolder = files[i];
                        // 删除文件夹
                        deleteRecursive(oldFolder);
                    }
                }
            }
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        SharedPreferences sharedPreferences = getSharedPreferences("data", 0);
        //这一段用于启动fileObserver，备份玩家存档
        isFileObserverLaunched = sharedPreferences.getBoolean("autoBackUp", true);
        if (isFileObserverLaunched) {
            checkAndDeleteOldBackups();
            File userdata = new File(getExternalFilesDir(null), "userdata");
            fileObserver = new FileObserver(userdata.getAbsolutePath(), FileObserver.CLOSE_WRITE) {
                @Override
                public void onEvent(int i, String s) {
                    try {
                        Calendar calendar = Calendar.getInstance();
                        File destDir = new File(getExternalFilesDir(null), String.format(Locale.getDefault(), "%d月%02d日%02d:%02d_userdata备份", calendar.get(Calendar.MONTH) + 1, calendar.get(Calendar.DAY_OF_MONTH), calendar.get(Calendar.HOUR_OF_DAY), calendar.get(Calendar.MINUTE)));
                        copyDir(userdata, destDir);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            };
            fileObserver.startWatching();
        }
    }

    @Override
    public void onDestroy() {
        if (isFileObserverLaunched) fileObserver.stopWatching();
        super.onDestroy();
    }

    private boolean isAddonWindowLoaded = false;
    private final HashMap<Integer, Integer> keyMap = new HashMap<>();

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (!isAddonWindowLoaded) {
            isAddonWindowLoaded = true;
            //Hook，启动！
            System.loadLibrary("SecondPlayer");
            SharedPreferences sharedPreferences = getSharedPreferences("data", 0);

            //读取设置中的“手动收集阳光金币”设置项，决定是否开启手动收集
            if (sharedPreferences.getBoolean("enableManualCollect", false))
                nativeEnableManualCollect();

            //读取设置中的“去除草丛和电线杆”设置项，决定是否使用新暂停菜单
            if (sharedPreferences.getBoolean("hideCoverLayer", false))
                nativeHideCoverLayer();


            keyMap.put(sharedPreferences.getInt("P1PAUSE", KeyEvent.KEYCODE_ESCAPE), 5);

            keyMap.put(KeyEvent.KEYCODE_ENTER, 6);
            keyMap.put(sharedPreferences.getInt("P1A", KeyEvent.KEYCODE_1), 6);
            keyMap.put(sharedPreferences.getInt("P1B", KeyEvent.KEYCODE_2), 7);
            keyMap.put(sharedPreferences.getInt("P1X", KeyEvent.KEYCODE_3), 8);
//            keyMap.put(sharedPreferences.getInt("P1Y", KeyEvent.KEYCODE_4), 9);

            keyMap.put(sharedPreferences.getInt("P1L1", KeyEvent.KEYCODE_0), 10);
            keyMap.put(sharedPreferences.getInt("P1R1", KeyEvent.KEYCODE_PERIOD), 11);
//            keyMap.put(sharedPreferences.getInt("P1L2", KeyEvent.KEYCODE_5), 12);
//            keyMap.put(sharedPreferences.getInt("P1R2", KeyEvent.KEYCODE_6), 13);
//
//            keyMap.put(sharedPreferences.getInt("P1TL", KeyEvent.KEYCODE_7), 14);
//            keyMap.put(sharedPreferences.getInt("P1TR", KeyEvent.KEYCODE_8), 15);

            keyMap.put(sharedPreferences.getInt("P1UP", KeyEvent.KEYCODE_DPAD_UP), 16);
            keyMap.put(sharedPreferences.getInt("P1DOWN", KeyEvent.KEYCODE_DPAD_DOWN), 17);
            keyMap.put(sharedPreferences.getInt("P1LEFT", KeyEvent.KEYCODE_DPAD_LEFT), 18);
            keyMap.put(sharedPreferences.getInt("P1RIGHT", KeyEvent.KEYCODE_DPAD_RIGHT), 19);


            keyMap.put(sharedPreferences.getInt("P2A", KeyEvent.KEYCODE_J), 6 + 256);
            keyMap.put(sharedPreferences.getInt("P2B", KeyEvent.KEYCODE_K), 7 + 256);
            keyMap.put(sharedPreferences.getInt("P2X", KeyEvent.KEYCODE_L), 8 + 256);
//            keyMap.put(sharedPreferences.getInt("P2Y", KeyEvent.KEYCODE_SEMICOLON), 9 + 256);

            keyMap.put(sharedPreferences.getInt("P2L1", KeyEvent.KEYCODE_Q), 10 + 256);
            keyMap.put(sharedPreferences.getInt("P2R1", KeyEvent.KEYCODE_E), 11 + 256);
//            keyMap.put(sharedPreferences.getInt("P2L2", KeyEvent.KEYCODE_U), 12 + 256);
//            keyMap.put(sharedPreferences.getInt("P2R2", KeyEvent.KEYCODE_I), 13 + 256);
//
//            keyMap.put(sharedPreferences.getInt("P2TL", KeyEvent.KEYCODE_O), 14 + 256);
//            keyMap.put(sharedPreferences.getInt("P2TR", KeyEvent.KEYCODE_P), 15 + 256);

            keyMap.put(sharedPreferences.getInt("P2UP", KeyEvent.KEYCODE_W), 16 + 256);
            keyMap.put(sharedPreferences.getInt("P2DOWN", KeyEvent.KEYCODE_S), 17 + 256);
            keyMap.put(sharedPreferences.getInt("P2LEFT", KeyEvent.KEYCODE_A), 18 + 256);
            keyMap.put(sharedPreferences.getInt("P2RIGHT", KeyEvent.KEYCODE_D), 19 + 256);


        }
    }
    public static native void nativeEnableManualCollect();//要求开启手动收集。

    public static native void nativeHideCoverLayer();
    public static native boolean nativeShouldSendKeyEvent();//返回是否需要直接将按键发送给Native层

    public static native void nativeSendKeyEvent(boolean isKeyDown, int keyCode);//发送按键

    // 左摇杆上 0
    // 左摇杆下 1
    // 左摇杆左 2
    // 左摇杆右 3

    // 未知键 4
    // 暂停键 5

    // A 6
    // B 7
    // X 8
    // Y 9

    // L1 10
    // R1 11
    // L2 12
    // R2 13

    // TL 14
    // TR 15

    // 上 16
    // 下 17
    // 左 18
    // 右 19

    // 玩家2的键值在上述键值的基础上添加256即可

    @Override // com.transmension.mobile.NativeActivity
    public void onNativeKeyEvent(KeyEvent event) {
        if (!event.isSystem())
            if (nativeShouldSendKeyEvent()) {
                Integer i = keyMap.get(event.getKeyCode());
                if (i != null) nativeSendKeyEvent(event.getAction() == KeyEvent.ACTION_DOWN, i);
                return;
            }
        super.onNativeKeyEvent(event);
    }
}