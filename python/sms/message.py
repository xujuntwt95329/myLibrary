# -*- coding: utf-8 -

from qcloudsms_py import SmsSingleSender
from qcloudsms_py.httpclient import HTTPError
from sms_config import *
import time


# 需要发送短信的手机号码
phone_numbers = ["xxxxxxxxxxx"]

ssender = SmsSingleSender(appid, appkey)

now = time.strftime('%m-%d %H:%M', time.localtime(time.time()))

params = [now, "1000", "25", "12000"]  # 当模板没有参数时，`params = []`，数组具体的元素个数和模板中变量个数必须一致，例如事例中templateId:5678对应一个变量，参数数组中元素个数也必须是一个

try:
    result = ssender.send_with_param(86, phone_numbers[0],
        template_id, params, extend="", ext="")  # 签名参数未提供或者为空时，会使用默认签名发送短信
except HTTPError as e:
    print(e)
except Exception as e:
    print(e)

print(result)