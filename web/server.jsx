import React from 'react';
import ReactDOMServer from 'react-dom/server';

import App from './app';

global.make = url => {
  return `<div id=\"root\">${ReactDOMServer.renderToString(<App />)}</div>`;
};
