import React from 'react';
import impoartedComponent from 'react-imported-component';
import { Route } from 'react-router';

import Home from './routes/Home';
import Product from './routes/Product';

const Lazy = impoartedComponent(() => import('./routes/Lazy'));

const App = () => {
  return (
    <div>
      <Route path="/" exact component={Home} />
      <Route path="/product/:productId" component={Product} />
      <Route path="/lazy" exact component={Lazy} />
    </div>
  );
};

export default App;
