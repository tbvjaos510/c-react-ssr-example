import './imported.js';

import React from 'react';
import ReactDOM from 'react-dom';
import { rehydrateMarks } from 'react-imported-component';
import { BrowserRouter } from 'react-router-dom';

import App from './app';

rehydrateMarks().then(() => {
  ReactDOM.hydrate(
    <BrowserRouter>
      <App />
    </BrowserRouter>,
    document.getElementById("root")
  );
})

