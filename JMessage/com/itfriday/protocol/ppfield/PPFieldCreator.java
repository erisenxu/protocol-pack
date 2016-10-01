package com.itfriday.protocol.ppfield;

/**
 * Created by erisenxu on 2016/9/4.
 */
public interface PPFieldCreator<E> {
    /**
     * 创建一个PPField对象
     * @return 返回创建的对象
     */
    E create();
}
