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
		LOGGER.info("Hello World!");
		BTJoystick js = new BTJoystick();
		//js.jsQuery();
		//js.readEvent();
		readEvent(js);
		
	}

	private static void readEvent(BTJoystick js) {
		while(true) {
			int[] event = js.readEvent();
			if(event.length == 4) {
				int time = event[0];
				int type = event[1];
				int number = event[2];
				int value = event[3];
				LOGGER.info("time :{}, type :{}, number :{}, value :{}", time, type, number, value);
				if(time > 0) {
				}else {
					LOGGER.error("empty event");
					try {
						Thread.sleep(10);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}else {
				LOGGER.error("invalid event length");
			}
		}
	}
}
