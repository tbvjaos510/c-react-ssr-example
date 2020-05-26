import React from 'react';
import { useRouteMatch } from 'react-router';

const Product = () => {
  const { params } = useRouteMatch();
  return <div>Product {params.productId}</div>;
};

export default React.memo(Product);
