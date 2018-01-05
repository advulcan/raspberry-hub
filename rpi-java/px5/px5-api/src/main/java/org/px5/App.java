package org.px5;

import java.io.IOException;

import org.px5.io.jni.BTJoystick;
import org.px5.util.JNIUtil;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Hello world!
 *
 */
public class App {
	private static Logger LOGGER = LoggerFactory.getLogger(App.class);
	
	public static void main(String[] args) {
		try {
			JNIUtil.loadLibraryFromJar("/libbtjoystick.so");
		} catch (IOException e) {
			e.printStackTrace();
			LOGGER.error(e.getMessage());
		}
		LOGGER.info("Hello World!");
		BTJoystick js = new BTJoystick();
		js.jsQuery();
	}
}
