//
// AUTO GENERATED FILE
//

#ifndef APP_CRAWIOT_MAIN_PAGE_H
#define APP_CRAWIOT_MAIN_PAGE_H

const char* CrawiotIndexPage = "<!DOCTYPE html><html lang=\"en\">  <head>    <meta charset=\"UTF-8\" />    <title>Crawiot</title>    <link      rel=\"stylesheet\"      href=\"https://unpkg.com/purecss@2.0.6/build/pure-min.css\"      integrity=\"sha384-Uu6IeWbM+gzNVXJcM9XV3SohHtmWE+3VGi496jvgX1jyvDTXfdK+rfZc8C1Aehk5\"      crossorigin=\"anonymous\"    />    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />  </head>  <body>    <header class=\"header\">      <h1>Crawiot</h1>      <h2>Control panel</h2>    </header>    <div class=\"content\">      <section class=\"content-section\" style=\"display: none\">        <div id=\"statusMessage\" class=\"message\"></div>      </section>      <section class=\"content-section\">        <form          action=\"/api/target\"          class=\"pure-form pure-form-aligned\"          method=\"post\"        >          <fieldset class=\"controls-wrapper\">            <div class=\"pure-control-group\">              <label for=\"X\">Координата X</label>              <input required type=\"number\" name=\"X\" id=\"X\" />            </div>            <div class=\"pure-control-group\">              <label for=\"Y\">Координата Y</label>              <input required type=\"number\" name=\"Y\" id=\"Y\" />            </div>            <div class=\"pure-control-group\">              <label>Задать цель</label>              <button type=\"submit\" class=\"pure-button pure-button-primary\">                Submit              </button>            </div>          </fieldset>        </form>      </section>      <section class=\"content-section\">        <div class=\"controls-wrapper\">          <a class=\"link\" href=\"/api/traces\" target=\"_blank\">Link to traces</a>        </div>      </section>    </div>    <style>      body {        color: #777;      }      .content {        margin: 10px auto;        padding: 0 2em;        line-height: 1.6em;      }      .header {        margin: 0 2em;        color: #333;        text-align: center;        padding: 2.5em 2em 0 2em;      }      .header h1 {        margin: 0.2em 0;        font-size: 2em;        font-weight: 300;      }      .header h2 {        font-weight: 300;        font-size: 1.5em;        color: #ccc;        padding: 0;        margin-top: 0;      }      .content-section {        border-top: 1px solid #eee;      }      .content-section:last-child {        border-top: 0;      }      .controls-wrapper {        width: max-content;        margin-left: auto !important;        margin-right: auto !important;        padding-top: 1em !important;      }      .pure-controls {        margin-top: 1em !important;      }      .pure-button {        float: right;      }      @media only screen and (max-width: 480px) {        .pure-button {          float: left;        }      }      .message {        border-radius: 4px;        padding: 1em;        width: fit-content;        margin: 1em auto;      }      .success {        background: #5aba59;        color: #fff;      }      .error {        background: #df2d4f;        color: #fff;      }    </style>    <script>      const urlParams = new URLSearchParams(window.location.search);      const xVal = urlParams.get(\"x\");      const yVal = urlParams.get(\"y\");      const isSuccess = urlParams.get(\"success\");      if (xVal != null && !isNaN(Number(xVal))) {        document.getElementById(\"X\").value = xVal;      }      if (yVal != null && !isNaN(Number(yVal))) {        document.getElementById(\"Y\").value = yVal;      }      const messageElement = document.getElementById(\"statusMessage\");      const showMessageSection = () =>        (messageElement.parentElement.style = \"\");      if (isSuccess === \"true\") {        messageElement.textContent = \"Device accepted the target\";        messageElement.classList.add(\"success\");        showMessageSection();      } else if (isSuccess === \"false\") {        messageElement.textContent = \"Target dismissed\";        messageElement.classList.add(\"error\");        showMessageSection();      }    </script>  </body></html>"

#endif //APP_CRAWIOT_MAIN_PAGE_H