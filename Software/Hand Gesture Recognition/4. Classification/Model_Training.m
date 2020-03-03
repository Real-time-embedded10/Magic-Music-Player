ges = 6; % 6 gesture: forward, backward, up, down, left, right
[sample,num] = size(feature); 
w = zeros(ges,num); 
y = zeros(ges,sample); 
b = zeros(ges,1); 

for i = 1:ges 
y(i,(i-1)*(sample/ges)+1:i*(sample/ges)) = 1;
end


loss_t = zeros(1,1500);

for step = 1:1500 
w_gre = zeros(ges,num); 
b_gre = zeros(ges,1); 
loss = 0; 

% Loss calculation
for old = 1:sample
y_pre = softmax(w*fea(old,:)'+b);
loss = loss + -y(:,old)'*log(y_pre);
end
loss = loss/sample;

% bias gradient vector computation
for i = 1:ges
loss_new1 = 0;
b_new = b;
b_new(i,1) = b_new(i,1) + 0.0001;
for new = 1:sample
y_pre = softmax(w*fea(new,:)'+b_new);
loss_new1 = loss_new1 + -y(:,new)'*log(y_pre);
end
loss_new1 = loss_new1/sample;
b_gre(i,1) = (loss_new1 - loss)/0.0001;
end

% weights gradient matrix computation
for i = 1:ges
for j = 1:num
loss_new2 = 0;
w_new = w;
w_new(i,j) = w_new(i,j) + 0.0001;
for new = 1:sample
y_pre = softmax(w_new*fea(new,:)'+b);
loss_new2 = loss_new2 + -y(:,new)'*log(y_pre);
end
loss_new2 = loss_new2/sample;
w_gre(i,j) = (loss_new2 - loss)/0.0001;
end
end

b = b - b_gre 
w = w - w_gre
loss_t(step) = loss;
end
% Output are 'w' and 'b'
