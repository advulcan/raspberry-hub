package org.px5.io.jni;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class BTJoystick {
	private static Logger LOGGER = LoggerFactory.getLogger(BTJoystick.class);
	public native int jsInput(int in);
	public native int jsQuery();
	public native int[] readEvent();
	public native void init(String callbackName, String callbackSignature);
	public void refresh(int [] maps) {
		LOGGER.info("refresh");
	}
}
