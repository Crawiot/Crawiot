$mainPageVariableValue = "";

$mainPageVariableValue = [System.String]::Join("", [System.IO.File]::ReadAllLines(".\Resources\index.html")).Replace('"', '\"');

$fileContent = @"
//
// AUTO GENERATED FILE
//

#ifndef APP_CRAWIOT_MAIN_PAGE_H
#define APP_CRAWIOT_MAIN_PAGE_H

const char* CrawiotIndexPage = "$mainPageVariableValue"

#endif //APP_CRAWIOT_MAIN_PAGE_H
"@

Set-Content -Path ".\app\crawiot_main_page.h" -Value $fileContent