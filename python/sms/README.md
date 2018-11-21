# Short message from Tencent Cloud Service

## Install Tencent SMS Python SDK
``` shell
pip install qcloudsms_py
```

## Input related parameters in `sms_config.py`
- `appid`  
- `appkey`  
- `template_id`   


## Input phone numbers in `message.py`
``` python
phone_numbers = ["xxxxxxxxxxx","xxxxxxxxxxx","xxxxxxxxxxx"]
```


## Finish params list
``` python
params = []
params.append(param1)
params.append(param2)
# ...
```

## Send message with single sender or multisender
``` python
ssender = SmsSingleSender(appid, appkey)
result = ssender.send_with_param(86, phone_numbers[0],
	template_id, params, extend="", ext="")
# or
ssender = SmsMultiSender(appid, appkey)
result = ssender.send_with_param(86, phone_numbers,
	template_id, params, extend="", ext="")
```



