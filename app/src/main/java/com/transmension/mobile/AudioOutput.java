package com.transmension.mobile;

import android.content.Context;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Build;

import java.nio.ByteBuffer;

/* loaded from: classes.dex */
public class AudioOutput {
    byte[] mAudioData = new byte[8192];
    private MobileAudioTrack mAudioTrack;
    private final Context mContext;

    public AudioOutput(Context context) {
        this.mContext = context;
    }


    public int getPreferredSampleRate() {
        if (Build.VERSION.SDK_INT < 17) {
            return -1;
        }
        AudioManager audioManager = (AudioManager) this.mContext.getSystemService(Context.AUDIO_SERVICE);
        String v = audioManager.getProperty("android.media.property.OUTPUT_SAMPLE_RATE");
        if (v != null) {
            return Integer.parseInt(v);
        }
        return -1;
    }


    public int getPreferredFramesPerBuffer() {
        if (Build.VERSION.SDK_INT < 17) {
            return -1;
        }
        AudioManager audioManager = (AudioManager) this.mContext.getSystemService(Context.AUDIO_SERVICE);
        String v = audioManager.getProperty("android.media.property.OUTPUT_FRAMES_PER_BUFFER");
        if (v != null) {
            return Integer.parseInt(v);
        }
        return -1;
    }

    public boolean setup(int sampleRate, int channels, int bits) {
        if (this.mAudioTrack == null && sampleRate == 44100 && channels == 2 && bits == 16) {
            int bufferSize = AudioTrack.getMinBufferSize(sampleRate, 3, 2);
            this.mAudioTrack = new MobileAudioTrack(3, sampleRate, 3, 2, bufferSize, 1);
            if (this.mAudioTrack.getState() != 1) {
                this.mAudioTrack.release();
                this.mAudioTrack = null;
                return false;
            }
            this.mAudioTrack.setPlaybackPositionUpdateListener(new AudioTrack.OnPlaybackPositionUpdateListener() { // from class: com.transmension.mobile.AudioOutput.1
                @Override // android.media.AudioTrack.OnPlaybackPositionUpdateListener
                public void onMarkerReached(AudioTrack track) {
                }

                @Override // android.media.AudioTrack.OnPlaybackPositionUpdateListener
                public void onPeriodicNotification(AudioTrack track) {
                }
            });
            this.mAudioTrack.play();
            return true;
        }
        return false;
    }

    public synchronized void shutdown() {
        if (this.mAudioTrack != null) {
            this.mAudioTrack.stop();
            this.mAudioTrack.release();
            this.mAudioTrack = null;
        }
    }

    public synchronized void write(ByteBuffer data, int offset, int len) {
        if (this.mAudioTrack != null) {
            data.position(offset);
            data.get(this.mAudioData, 0, len);
            this.mAudioTrack.write(this.mAudioData, 0, len);
        }
    }

    public synchronized void onPause() {
        if (this.mAudioTrack != null && this.mAudioTrack.getPlayState() == 3) {
            this.mAudioTrack.pause();
        }
    }

    public synchronized void onResume() {
        if (this.mAudioTrack != null && this.mAudioTrack.getPlayState() != 3) {
            this.mAudioTrack.play();
        }
    }
}