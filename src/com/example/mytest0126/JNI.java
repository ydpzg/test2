package com.example.mytest0126;

import junit.framework.Test;
import android.util.Log;

public class JNI {
	public static native int connect1(int src);
	public static native int connect2(int src);
	public static native void closeConnection1();
	public static native void closeConnection2();
	public static native void sendToServer1(String inf);
	public static native void sendToServer2(String inf);
	static
    {
//    	Log.i("test", System.getProperty("java.library.path"));
		System.loadLibrary("socket_client");
        System.loadLibrary("testGet");
    }
}
