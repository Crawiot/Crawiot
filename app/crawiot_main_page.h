//
// AUTO GENERATED FILE
//

#ifndef APP_CRAWIOT_MAIN_PAGE_H
#define APP_CRAWIOT_MAIN_PAGE_H

const char* CrawiotIndexPage = "<!DOCTYPE html><html lang=\"en\">  <head>    <meta charset=\"UTF-8\" />    <title>Crawiot</title>    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />  </head>  <body>    <header class=\"header\">      <h1>Crawiot</h1>      <h2>Control panel</h2>    </header>    <div class=\"content\">      <section class=\"content-section\" style=\"display: none\">        <div id=\"statusMessage\" class=\"message\"></div>      </section>      <section class=\"content-section\">        <form action=\"/api/target\" class=\"pure-form\" method=\"post\">          <fieldset class=\"controls-wrapper\">            <div class=\"pure-control-group\">              <label for=\"X\">X</label>              <input required type=\"number\" name=\"X\" id=\"X\" />            </div>            <div class=\"pure-control-group\">              <label for=\"Y\">Y</label>              <input required type=\"number\" name=\"Y\" id=\"Y\" />            </div>            <div class=\"pure-control-group\">              <button type=\"submit\" class=\"pure-button pure-button-primary\">                Submit              </button>            </div>          </fieldset>        </form>      </section>      <section class=\"content-section\">        <div class=\"controls-wrapper\">          <a class=\"link\" href=\"/api/traces\" target=\"_blank\">Link to traces</a>        </div>      </section>    </div>    <style>      html {        font-family: sans-serif;        line-height: 1.15;      }      body {        color: #777;        margin: 0;      }      .content {        margin: 10px auto;        padding: 0 2em;        line-height: 1.6em;      }      .header {        margin: 0 2em;        color: #333;        text-align: center;        padding: 2.5em 2em 0 2em;      }      .header h1 {        margin: 0.2em 0;        font-size: 2em;        font-weight: 300;      }      .header h2 {        font-weight: 300;        font-size: 1.5em;        color: #ccc;        padding: 0;        margin-top: 0;      }      .controls-wrapper {        width: max-content;        margin-left: auto !important;        margin-right: auto !important;        padding-top: 1em !important;      }      .pure-form fieldset {        margin: 0;        padding: 0.35em 0 0.75em;        border: 0;      }      .pure-button {        font-family: inherit;        font-size: 100%;        padding: 0.5em 1em;        color: rgba(0, 0, 0, 0.8);        border: none transparent;        background-color: #e6e6e6;        text-decoration: none;        border-radius: 2px;      }      .pure-button-primary {        background-color: #0078e7;        color: #fff;      }      .pure-form input[type=\"number\"] {        font-family: inherit;        font-size: 100%;        line-height: 1.15;        margin: 0;        padding: 0.5em 0.6em;        display: inline-block;        border: 1px solid #ccc;        -webkit-box-shadow: inset 0 1px 3px #ddd;        box-shadow: inset 0 1px 3px #ddd;        border-radius: 4px;        vertical-align: middle;        -webkit-box-sizing: border-box;        box-sizing: border-box;      }      .pure-controls {        margin-top: 1em !important;      }      .pure-button {        float: right;      }      .message {        border-radius: 4px;        padding: 1em;        width: 15%;        margin: 1em auto;        text-align: center;      }      .pure-control-group {        margin-bottom: 0.5em;      }      .pure-control-group label {        text-align: right;        display: inline-block;        vertical-align: middle;        margin: 0 1em 0 0;      }      @media only screen and (max-width: 480px) {        .pure-button {          float: left;        }        .message {          width: 70%;        }      }      .success {        background: #5aba59;        color: #fff;      }      .error {        background: #df2d4f;        color: #fff;      }      .content-section {        border-top: 1px solid #eee;      }    </style>    <script>      const urlParams = new URLSearchParams(window.location.search);      const xVal = urlParams.get(\"x\");      const yVal = urlParams.get(\"y\");      const isSuccess = urlParams.get(\"success\");      if (xVal != null && !isNaN(Number(xVal))) {        document.getElementById(\"X\").value = xVal;      }      if (yVal != null && !isNaN(Number(yVal))) {        document.getElementById(\"Y\").value = yVal;      }      const messageElement = document.getElementById(\"statusMessage\");      const showMessageSection = () =>        (messageElement.parentElement.style = \"\");      if (isSuccess === \"true\") {        messageElement.textContent = \"Device accepted the target\";        messageElement.classList.add(\"success\");        showMessageSection();      } else if (isSuccess === \"false\") {        messageElement.textContent = \"Target dismissed\";        messageElement.classList.add(\"error\");        showMessageSection();      }    </script>  </body></html>";

#endif //APP_CRAWIOT_MAIN_PAGE_H
