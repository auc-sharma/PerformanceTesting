Action()
{
	
	web_add_header("Content-Type", "text/xml");
	
	web_reg_find("Search=Body",
		"SaveCount=Count",
		"Text=m:CapitalCityResult",
		LAST);

	web_reg_find("Fail=Found",
		"Search=Body",
		
		"Text=Country not found in the database",
		
		LAST);

	
	lr_start_transaction("Transaction_01");

	web_custom_request("web_custom_request",
		"URL=http://webservices.oorsprong.org/websamples.countryinfo/CountryInfoService.wso",
		"Method=POST",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		"Body=<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:web=\"http://www.oorsprong.org/websamples.countryinfo\">\r\n"
		"   <soapenv:Header/>\r\n"
		"   <soapenv:Body>\r\n"
		"      <web:CapitalCity>\r\n"
		"         <web:sCountryISOCode>{ISO_Code}</web:sCountryISOCode>\r\n"
		"      </web:CapitalCity>\r\n"
		"   </soapenv:Body>\r\n"
		"</soapenv:Envelope>",
		LAST);
	
	str = lr_eval_string("{Count}");
	i = atoi(str);
	
	
	if(i > 0)
	{
		lr_end_transaction("Transaction_01", LR_AUTO);
	}
	else
	{
	
	lr_end_transaction("Transaction_01", LR_FAIL);
	}

	return 0;
}
