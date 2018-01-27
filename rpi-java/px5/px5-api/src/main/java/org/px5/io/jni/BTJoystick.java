package org.px5.io.jni;

import java.io.IOException;

import org.px5.util.JNIUtil;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class BTJoystick {
	private static Logger LOGGER = LoggerFactory.getLogger(BTJoystick.class);
	private static boolean inited = false;
	static {
		try {
			JNIUtil.loadLibraryFromJar("/libbtjoystick.so");
			inited = true;
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	/*public BTJoystick() {
		super();
	}*/
	public native int jsInput(int in);
	public native int jsQuery();
	public native int[] readEvent();
	public native void init(String callbackName, String callbackSignature);
	public void refresh(int [] maps) {
		LOGGER.info("refresh");
	}
}
