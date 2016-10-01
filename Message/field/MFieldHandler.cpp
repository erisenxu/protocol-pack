/*
 * @(#) MFieldHandler.cpp Created on 2014-03-27
 *
 * Copyright (c) 2014-2016 Erisen Xu (@itfriday)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "MFieldHandler.h"
#include "comm/MBaseFuncDef.h"
#include <string.h>

/**
 * 构造函数
 */
MFieldHandler::MFieldHandler()
    : m_pstParent(NULL),
      m_ullClientData(0)
{
    memset(m_szFieldName, 0, sizeof(m_szFieldName));
}

/**
 * 设置字段的名称
 * @param szFieldName 字段的名称
 */
void MFieldHandler::setFieldName(const char* szFieldName)
{
    if (NULL == szFieldName) return;
    STRNCPY(m_szFieldName, sizeof(m_szFieldName), szFieldName, sizeof(m_szFieldName));
}

