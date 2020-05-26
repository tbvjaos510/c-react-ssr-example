import '@babel/polyfill';

import React from 'react';
import ReactDOMServer from 'react-dom/server';
import { printDrainHydrateMarks } from 'react-imported-component';
import { StaticRouter } from 'react-router';

import App from './app';

global.make = (url) => {
  return `<div id=\"root\">${ReactDOMServer.renderToString(
    <StaticRouter location={url}>
      <App />
    </StaticRouter>
  )}</div>` + printDrainHydrateMarks();
};
